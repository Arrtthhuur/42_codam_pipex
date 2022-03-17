/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrapper.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 12:40:36 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/17 14:52:41 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h> // perror
#include <unistd.h> // close

/*
** Wrapper functions.
*/

void	perror_wrap(char *msg)
{
	perror(msg);
	exit(FAILURE);
}

void	dup2_wrap(int fd1, int fd2)
{
	perror("dup2 error");
	close(fd1);
	close(fd2);
	exit(FAILURE);
}

int	fork_wrap(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		return (FAILURE);
	}
	return (pid);
}
