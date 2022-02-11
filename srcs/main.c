/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:56:51 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/11 18:10:34 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

// #include <stdlib.h>
#include <unistd.h> // pipe
#include <stdio.h> // printf

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_cmd	cmds[2];

	if (argc != 5)
		error_exit(1, "Usage: ./pipex file1 cmd1 cmd2 file2");
	open_files(fd, argv[1], argv[4]);
	build_cmd(cmds[0], cmds[1], argv);
	// pipex(fd[0], fd[1], cmds, envp);
	return (0);
}
