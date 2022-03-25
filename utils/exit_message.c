/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_message.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/08 15:57:26 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/24 16:50:48 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // write

int	error_msg(char *msg)
{
	write(2, "Error\n", 7);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (EXIT_FAILURE);
}

int	success_msg(char *msg)
{
	write(2, "Success\n", 9);
	if (msg)
		write(2, msg, ft_strlen(msg));
	return (EXIT_SUCCESS);
}

void	error_exit(int errnum, char *msg)
{
	write(2, "/pipex: ", 9);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(errnum);
}
