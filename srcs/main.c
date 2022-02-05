/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:56:51 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/05 13:28:22 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	fd1;
	int	fd2;

	if (argc != 5)
		error_exit(1, "Usage: ./pipex file1 cmd1 cmd2 file2");
	open_files(&fd1, argv[1], &fd2, argv[4]);
	return (0);
}
