/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_grid.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/31 12:48:52 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/31 12:51:57 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** Free double pointer array.
*/
void	free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}
