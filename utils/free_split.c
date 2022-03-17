/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_split.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/17 12:55:24 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/17 12:57:11 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
