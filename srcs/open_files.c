/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 13:28:12 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/11 15:48:53 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


static int	open_outfile(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == ERROR)
		error_exit(3, "Failure reading outfile");
	return (fd);
}

static int	open_infile(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		error_exit(2, "Infile read fail");
	return (fd);
}

void	open_files(int fd[2], char *file1, char *file2)
{
	fd[0] = open_infile(file1);
	fd[1] = open_outfile(file2);
}
