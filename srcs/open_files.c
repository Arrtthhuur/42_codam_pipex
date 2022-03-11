/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 13:28:12 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/11 13:47:50 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
** Open output file.
*/
static int	outfile_open(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == ERROR)
		error_exit(2, "open outfile");
	return (fd);
}

/*
** Open input file.
*/
static int	infile_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == ERROR)
		error_exit(2, "open infile");
	return (fd);
}

/*
** Separate in and output.
*/
void	files_open(int fd[2], char *file1, char *file2)
{
	fd[0] = infile_open(file1);
	fd[1] = outfile_open(file2);
}
