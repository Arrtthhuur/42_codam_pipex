/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:45:07 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/21 15:09:43 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // fork
#include <stdio.h> // perror

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

/*
** Build path of given command and execute.
*/
static void	cmd_exec(t_cmd cmd, char **envp)
{
	cmd.cmd = path_build(cmd, envp);
	write(2, cmd.cmd, ft_strlen(cmd.cmd));
	write(2, "\n", 1);
	// printf("cmd = %s", cmd.cmd);
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
static void	child1(int pend[2], char **argv, t_cmd cmd, char **envp)
{
	int	fd_in;

	fd_in = open(argv[1], O_RDONLY);
	if (fd_in == FAILURE)
		perror_wrap("open infile error");
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
static void	child2(int pend[2], char **argv, t_cmd cmd, char **envp)
{
	int	fd_out;

	fd_out = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd_out == FAILURE)
		perror_wrap("open outfile error");
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
** printf("child2 status %d\n", status);
*/
static int	parent(int pend[2], pid_t pid1, pid_t pid2)
{
	int		status;

	close(pend[READ]);
	close(pend[WRITE]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (SUCCESS);
}

/*
** Pipe, fork child1, fork child2 and parent.
*/
int	pipex(char **argv, t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	// int		fd[2];
	int		pend[2];
	pid_t	pid1;
	pid_t	pid2;

	// files_open(fd, argv[1], argv[4]);
	if (pipe(pend) == FAILURE)
		perror_wrap("pipe error");
	pid1 = fork_wrap();
	if (pid1 == CHILD)
		child1(pend, argv, *cmd1, envp);
	pid2 = fork_wrap();
	if (pid2 == CHILD)
		child2(pend, argv, *cmd2, envp);
	return (parent(pend, pid1, pid2));
}
