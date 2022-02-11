/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:45:07 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/11 16:13:53 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // fork

// void	run_source(t_cmd cmd, char **arg, char **envp, int fd)
// {
// 	char 	*ls[] = { "/bin/ls", 0, 0 };

// 	dup2(fd, 1);
// 	// close(fd);
// 	execve(cmd.path, ls, envp);
// 	// perror(cmd1[0]);
// }

// void	run_dest(t_cmd cmd, char **arg, char **envp, int fd)	/* run the second part of the pipeline, cmd2 */
// {
// 	char 	*wc[] = { "/usr/bin/wc", 0, 0 };

// 	// cmd.file = get_cmd(cmd, argv, envp);
// 	dup2(fd, 0);
// 	// close(pfd[1]);
// 	execve(cmd.path, wc, envp);
// 	// perror(cmd2[0]);
// }

int	pipex(int fd1, int fd2, t_cmd cmds[2], char **envp)
{
	int	pid1;
	int	pid2;
	int	fd[2];

	if (pipe(fd) == ERROR)
		error_exit(3, "Pipe fail");
	pid1 = fork();
	if (pid1 == ERROR)
		error_exit(6, "Fork fail #1");
	else if (pid1 == CHILD)
		run_source();
	pid2 = fork();
	if (pid2 == ERROR)
		error_exit(7, "Fork fail #2");
	else if (pid2 == CHILD)
		run_dest();
}
