/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:45:07 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/19 15:28:10 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // fork
#include <stdio.h> // perror

static void	cmd_exec(t_cmd cmd, char **envp)
{
	cmd.cmd = path_build(cmd, envp);
	printf("cmd.cmd = %s\n", cmd.cmd); // remove for eval
	if (!cmd.cmd)
		return (error_exit(5, "command not found"));
	if (execve(cmd.cmd, cmd.args, envp) == ERROR)
		return (perror("execve"));
	error_exit(666, "command execution fail");
}

static void	src_exec(int pend[2], int fd_in, t_cmd cmd, char **envp)
{	
	if (dup2(fd_in, STDIN_FILENO) == ERROR)
		return (perror("dup2 fd_in"));
	if (dup2(pend[WRITE], STDOUT_FILENO) == ERROR)
		return (perror("dup2 pipe write"));
	close(fd_in);
	close(pend[READ]);
	cmd_exec(cmd, envp);
}

static void	dst_exec(int pend[2], int fd_out, t_cmd cmd, char **envp)
{
	if (dup2(pend[READ], STDIN_FILENO) == ERROR)
		return (perror("dup2 pipe read"));
	if (dup2(fd_out, STDOUT_FILENO) == ERROR)
		return (perror("dup2 fd_out"));
	close(fd_out);
	close(pend[WRITE]);
	cmd_exec(cmd, envp);
}

static void	parent(int pend[2], pid_t pid1, pid_t pid2)
{
	int		status;

	close(pend[READ]);
	close(pend[WRITE]);
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
}

void	pipex(int fd[2], t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		pend[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(pend) == ERROR)
		return (perror("pipe"));
	pid1 = fork();
	if (pid1 == ERROR)
		return (perror("fork cmd1"));
	else if (pid1 == CHILD)
		src_exec(pend, fd[0], *cmd1, envp);
	pid2 = fork();
	if (pid2 == ERROR)
		return (perror("fork cmd2"));
	else if (pid2 == CHILD)
		dst_exec(pend, fd[1], *cmd2, envp);
	parent(pend, pid1, pid2);
}
