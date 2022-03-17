/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:45:07 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/17 14:56:25 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // fork
#include <stdio.h> // perror

/*
** Build path of given command and execute.
*/
static void	cmd_exec(t_cmd cmd, char **envp)
{
	cmd.cmd = path_build(cmd, envp);
	if (!cmd.cmd)
		error_exit(127, "command not found");
	if (execve(cmd.cmd, cmd.args, envp) == FAILURE)
		perror_wrap("execve error");
	error_exit(127, "command execution fail");
}

/*
** Redirect child1 and execute command.
** 1st dup2: we want fd_in to be execve() input.
** 2nd dup2: we want pend[1] to be execve() stdout.
** Close the end of the pipe we're not using => as long as it
** 	is open the other end will be waiting for input and won't
** 	finish its process.
*/
static void	child1(int pend[2], int fd_in, t_cmd cmd, char **envp)
{	
	if (dup2(fd_in, STDIN_FILENO) == FAILURE)
		dup2_wrap(fd_in, pend[WRITE]);
	if (dup2(pend[WRITE], STDOUT_FILENO) == FAILURE)
		dup2_wrap(fd_in, pend[WRITE]);
	close(fd_in);
	close(pend[READ]);
	cmd_exec(cmd, envp);
}

/*
** Redirect child2 and execute command.
** 1st dup2: fd_out is the stdout.
** 2nd dup2: pend[0] is the stdin.
*/
static void	child2(int pend[2], int fd_out, t_cmd cmd, char **envp)
{
	if (dup2(pend[READ], STDIN_FILENO) == FAILURE)
		dup2_wrap(fd_out, pend[READ]);
	if (dup2(fd_out, STDOUT_FILENO) == FAILURE)
		dup2_wrap(fd_out, pend[READ]);
	close(fd_out);
	close(pend[WRITE]);
	cmd_exec(cmd, envp);
}

/*
** Close pipe and wait for both child processes to finish.
** Return exit status if one of the children exited normally.
*/
static int	parent(int pend[2], pid_t pid1, pid_t pid2)
{
	int		status;

	close(pend[READ]);
	close(pend[WRITE]);
	waitpid(pid1, &status, 0);
	// printf("child1 status %d\n", status);
	waitpid(pid2, &status, 0);
	// printf("child2 status %d\n", status);
	if (WIFEXITED(status))
	{
		// printf("WIFEXITED\n");
		return (WEXITSTATUS(status));
	}
	return (SUCCESS);
}

/*
** Pipe, fork child1, fork child2 and parent.
*/
int	pipex(int fd[2], t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		pend[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pend) == FAILURE)
		perror_wrap("pipe error");
	pid1 = fork_wrap();
	if (pid1 == CHILD)
		child1(pend, fd[0], *cmd1, envp);
	pid2 = fork_wrap();
	if (pid2 == CHILD)
		child2(pend, fd[1], *cmd2, envp);
	return (parent(pend, pid1, pid2));
}
