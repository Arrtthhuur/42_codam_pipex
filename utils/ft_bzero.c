/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bzero.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/29 11:05:36 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/29 11:06:17 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*temp;

	temp = s;
	while (n > 0)
	{
		*temp = 0;
		temp++;
		n--;
	}
}
