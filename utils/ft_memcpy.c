/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:35:29 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/09 14:35:42 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	unsigned char	*temp_dst;
	unsigned char	*temp_src;

	temp_dst = (unsigned char *)dst;
	temp_src = (unsigned char *)src;
	if (temp_dst == NULL && temp_src == NULL)
		return (NULL);
	while (n > 0)
	{
		*temp_dst = *temp_src;
		temp_src++;
		temp_dst++;
		n--;
	}
	return (dst);
}
