/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:56:51 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/09 15:59:52 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// void	runsource(int pfd[])
// {
// 	int	pid;

// 	pid = fork();
// 	if (pid == -1)
// 		error_exit(4, "Fork fail (source)");
// 	if (pid == 0)
// 	{
// 		dup2(pfd[1], 1);
// 		close(pfd[0]);
// 		execve(cmd1[0], cmd1, 0);
// 		perror(cmd1[0]);
// 	}
// }

// void	rundest(int pfd[])	/* run the second part of the pipeline, cmd2 */
// {
// 	int pid;

// 	pid = fork();
// 	if (pid == -1)
// 	{
// 		perror("fork");
// 		exit(2);
// 	}
// 	if (pid == 0)
// 	{
// 		dup2(pfd[0], 0);
// 		close(pfd[1]);
// 		execve(cmd2[0], cmd2, 0);
// 		perror(cmd2[0]);	
// 	}
// }

char	*path_access(char **env_p, char *argv)
{
	char	*cmd1;
	int		i;

	i = 0;

	while ()
	cmd1 = ft_strjoin(*env_p, argv);
	printf("%s\n", cmd1);
	return (cmd1);
}

char	**path_join(char *path)
{
	char **envp;
	int i;

	envp = ft_split(path + 5, ':');
	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (envp);
}

char	*get_path_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return(envp[i]);
		i++;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	int	status;
	char	*path;
	t_cmd cmd;
	char	**env_p;

	if (argc != 5)
		error_exit(1, "Usage: ./pipex file1 cmd1 cmd2 file2");
	if (pipe(fd) == ERROR)
		error_exit(3, "Pipe fail");
	// open_files(fd[0], argv[1], fd[1], argv[4]);
	// runsource(fd);
	// rundest(fd);
	path = get_path_env(envp);
	env_p = path_join(path);
	path_access(env_p, argv[2]);
	return (0);
}
