/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 14:07:13 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/11 12:22:40 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	cmd_get(t_cmd *cmd, char *arg)
{
	int	i;

	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->args = NULL;
	i = 0;
	while (arg[i] != ' ')
		i++;
	cmd->path = ft_substr(arg, 0, i);
	if (!cmd->path)
		error_exit(4, "ft_substr cmd");
}
