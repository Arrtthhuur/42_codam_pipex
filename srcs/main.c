/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:56:51 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/19 13:06:17 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	t_cmd	cmd1;
	t_cmd	cmd2;

	if (argc != 5)
		error_exit(1, "Usage: ./pipex file1 cmd1 cmd2 file2");
	files_open(fd, argv[1], argv[4]);
	input_parser(&cmd1, &cmd2, argv[2], argv[3]);
	pipex(fd, &cmd1, &cmd2, envp);
	return (0);
}
