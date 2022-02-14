/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:45:07 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/14 15:42:45 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // fork
#include <stdio.h> //perror

static void	exec_cmd(t_cmd cmd, char **envp)
{
	char	*full_cmd;

	full_cmd = path_build(cmd, envp);
	if (!full_cmd)
		return (error_exit(8, "Command can't be found"));
	if (execve(full_cmd, cmd.args, envp) == ERROR)
		return (perror("Execve"));
	error_exit(666, "Failure to execute command");
}

static void	exec_src(int end[2], int fd_in, t_cmd cmd, char **envp)
{	
	if (dup2(fd_in, STDIN_FILENO) == ERROR)
		return (perror("Dup2 #1"));
	if (dup2(end[WRITE], STDOUT_FILENO) == ERROR)
		return (perror("Dup2 #2"));
	close(fd_in);
	close(end[READ]);
	exec_cmd(cmd, envp);
}

static void	exec_dst(int end[2], int fd_out, t_cmd cmd, char **envp)
{
	if (dup2(end[READ], STDIN_FILENO) == ERROR)
		return (perror("Dup2 #1"));
	if (dup2(fd_out, STDOUT_FILENO) == ERROR)
		return (perror("Dup2 #2"));
	close(fd_out);
	close(end[WRITE]);
	exec_cmd(cmd, envp);
}

static void	parent(int end[2], pid_t pid_1, pid_t pid_2)
{
	int		status;

	close(end[READ]);
	close(end[WRITE]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
}

void	pipex(int fd[2], t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		end[2];
	pid_t	pid_1;
	pid_t	pid_2;

	if (pipe(end) == ERROR)
		return (perror("Pipe"));
	pid_1 = fork();
	if (pid_1 == ERROR)
		return (perror("Fork #1"));
	else if (pid_1 == CHILD)
		exec_src(end, fd[0], *cmd1, envp);
	pid_2 = fork();
	if (pid_2 == ERROR)
		return (perror("Fork #2"));
	else if (pid_2 == CHILD)
		exec_dst(end, fd[1], *cmd2, envp);
	parent(end, pid_1, pid_2);
}
