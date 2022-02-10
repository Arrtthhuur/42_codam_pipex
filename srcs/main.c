/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:56:51 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/10 15:47:10 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// #include <stdlib.h>
#include <unistd.h> // pipe
#include <stdio.h> // printf

void	runsource(t_cmd cmd, int pfd[])
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_exit(4, "Fork fail (source)");
	if (pid == 0)
	{
		dup2(pfd[1], 1);
		close(pfd[0]);
		
		// execve(cmd1[0], cmd1, 0);
		perror(cmd1[0]);
	}
}

void	rundest(t_cmd cmd, int pfd[])	/* run the second part of the pipeline, cmd2 */
{
	int pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(2);
	}
	if (pid == 0)
	{
		cmd.file = get_cmd(cmd, argv, envp);
		dup2(pfd[0], 0);
		close(pfd[1]);
		execve(cmd2[0], cmd2, 0);
		perror(cmd2[0]);	
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid;
	t_cmd	cmd;

	if (argc != 5)
		error_exit(1, "Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(fd) == ERROR)
		error_exit(3, "Pipe fail");
	open_files(fd, argv[1], argv[4]);
	// cmd.file = get_cmd(cmd, argv, envp);
	printf("%s\n", cmd.file);
	run_source(cmd, fd);
	run_dest(cmd, fd);
	// execve(cmd.file, &cmd.file, envp);
	return (0);
}
