/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_cmd.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/19 14:07:13 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/19 14:19:10 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h> // printf

void	args_print(t_cmd cmd)
{
	int	i;

	i = 0;
	while (cmd.args[i])
	{
		printf("%s ", cmd.args[i]);
		i++;
	}
	printf("\n");
}

static void	cmd_init(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->path = NULL;
	cmd->args = NULL;
}

void	cmd_get(t_cmd *cmd, char *arg)
{
	int	i;

	cmd_init(cmd);
	i = 0;
	while (arg[i] != ' ')
		i++;
	cmd->path = ft_substr(arg, 0, i);
	if (!cmd->path)
		error_exit(4, "ft_substr cmd");
}