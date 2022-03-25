/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 12:00:30 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/24 12:03:01 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

size_t	ft_intlen(long n)
{
	size_t			len;
	unsigned int	num;

	len = 0;
	if (n <= 0)
	{
		num = n * -1;
		len++;
	}
	else
		num = n;
	while (num > 0)
	{
		num /= 10;
		len++;
	}
	return (len);
}
