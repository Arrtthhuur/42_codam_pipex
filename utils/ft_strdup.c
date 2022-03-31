/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/09 14:35:09 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/30 16:31:06 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*ft_strdup(const char *s1)
{
	char		*save;
	size_t		i;

	save = (char *)malloc(ft_strlen(s1) + 1);
	if (!save)
		return (NULL);
	i = 0;
	while (*s1)
	{
		save[i] = *s1;
		i++;
		s1++;
	}
	save[i] = '\0';
	return (save);
}
