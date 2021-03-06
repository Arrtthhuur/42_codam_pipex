/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:56:51 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/31 12:43:54 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** Main function, usage: ./pipex file1 cmd1 cmd2 file2
** Check nb of args, open files, parse input and pipex function.
*/
int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd1;
	t_cmd	cmd2;

	if (argc != 5)
		error_exit(1, "Usage: ./pipex file1 cmd1 cmd2 file2");
	input_parse(&cmd1, &cmd2, argv[2], argv[3]);
	return (pipex(argv, &cmd1, &cmd2, envp));
}
