/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:45:07 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/16 15:32:52 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // fork
#include <stdio.h> // perror

static void	exec_cmd(t_cmd cmd, char **envp)
{
	char	*full_cmd;

	full_cmd = path_build(cmd, envp);
	// printf("full cmd: %s\n", full_cmd);
	if (!full_cmd)
		return (error_exit(8, "command not found"));
	if (execve(full_cmd, cmd.args, envp) == ERROR)
		return (perror("Execve"));
	error_exit(666, "command execution fail");
}

static void	exec_src(int pend[2], int fd_in, t_cmd cmd, char **envp)
{	
	if (dup2(fd_in, STDIN_FILENO) == ERROR)
		return (perror("Dup2 #1"));
	if (dup2(pend[WRITE], STDOUT_FILENO) == ERROR)
		return (perror("Dup2 #2"));
	close(fd_in);
	close(pend[READ]);
	exec_cmd(cmd, envp);
}

static void	exec_dst(int pend[2], int fd_out, t_cmd cmd, char **envp)
{
	if (dup2(pend[READ], STDIN_FILENO) == ERROR)
		return (perror("Dup2 #1"));
	if (dup2(fd_out, STDOUT_FILENO) == ERROR)
		return (perror("Dup2 #2"));
	close(fd_out);
	close(pend[WRITE]);
	exec_cmd(cmd, envp);
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
		return (perror("Pipe"));
	pid1 = fork();
	if (pid1 == ERROR)
		return (perror("Fork #1"));
	else if (pid1 == CHILD)
		exec_src(pend, fd[0], *cmd1, envp);
	pid2 = fork();
	if (pid2 == ERROR)
		return (perror("Fork #2"));
	else if (pid2 == CHILD)
		exec_dst(pend, fd[1], *cmd2, envp);
	parent(pend, pid1, pid2);
}
