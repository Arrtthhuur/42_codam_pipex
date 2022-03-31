/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   wrapper.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/15 12:40:36 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/31 12:58:37 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h> // perror
#include <unistd.h> // close

/*
** Wrapper functions.
*/

void	perror_wrap(int errnum, char *msg)
{
	write(2, "/pipex: ", 8);
	perror(msg);
	exit(errnum);
}

void	dup2_wrap(int fd1, int fd2)
{
	perror("dup2");
	close(fd1);
	close(fd2);
	exit(FAILURE);
}

void	write_msg(char *msg)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 2);
}

void	write_notif(char *notify, char *msg)
{
	write(2, notify, ft_strlen(notify));
	write(2, ": ", 3);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 2);
}
