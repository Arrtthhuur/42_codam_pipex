/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:56:51 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/14 15:49:43 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// #include <stdlib.h>
#include <unistd.h> // pipe
#include <stdio.h> // printf

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_cmd	cmd1;
	t_cmd	cmd2;

	if (argc != 5)
		error_exit(1, "Usage: ./pipex file1 cmd1 cmd2 file2");
	open_files(fd, argv[1], argv[4]);
	build_cmd(&cmd1, &cmd2, argv[2], argv[3]);
	// get_path(&cmd1, &cmd2, argv, envp);
	printf("cmd1: %s %s at %s\n", cmd1.args[0], cmd1.args[1], cmd1.path);
	printf("cmd2: %s %s at %s\n", cmd2.args[0], cmd2.args[1], cmd2.path);
	pipex(fd, &cmd1, &cmd2, envp);
	return (0);
}
