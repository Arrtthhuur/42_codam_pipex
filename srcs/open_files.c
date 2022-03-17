/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   open_files.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/05 13:28:12 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/16 14:08:24 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/*
** Open output file.
** With create, write or truncate flags.
** rw-r-r access rights.
*/
static int	outfile_open(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == FAILURE)
		perror_wrap("open outfile error");
	return (fd);
}

/*
** Open input file.
** With read flag.
*/
static int	infile_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == FAILURE)
		perror_wrap("open infile error");
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
