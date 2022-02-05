/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 13:28:12 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/05 16:05:29 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static int	open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit(2, "Infile read fail\n");
	return (fd);
}

static int	open_outfile(char *file)
{
	int	fd;
}

void	open_files(int fd1, char *file1, int fd2, char *file2)
{
	fd1 = open_infile(file1);
	fd2 = open_outfile(file2);
}
