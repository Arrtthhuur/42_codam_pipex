/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/13 12:34:24 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/19 15:16:23 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h> // printf

static void	param_clean(char **args)
{
	int	i;
	int	x;

	i = 0;
	while (args[i])
	{
		if (args[i][0] == 39)
		{
			x = 1;
			while (args[i][x] != 39)
				x++;
			args[i] = ft_substr(args[i], 1, x - 1);
			if (!args[i])
				error_exit(4, "ft_substr clean");
		}
		i++;
	}
}

static t_cmd	param_split(char *arg)
{
	t_cmd	cmd;

	cmd_get(&cmd, arg);
	cmd.args = ft_split(arg, ' ');
	if (!cmd.args)
		error_exit(3, "ft_split param");
	param_clean(cmd.args);
	args_print(cmd); // remove for eval
	return (cmd);
}

void	input_parse(t_cmd *cmd1, t_cmd *cmd2, char *arg1, char *arg2)
{
	*cmd1 = param_split(arg1);
	*cmd2 = param_split(arg2);
}
