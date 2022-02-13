/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/13 12:34:24 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/13 15:50:34 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	get_cmd(char **path, char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != ' ')
		i++;
	*path = ft_substr(arg, 0, i);
	if (!*path)
		error_exit(3, "Substring failure");
}

t_cmd	param_split(char *arg)
{
	t_cmd	cmd;

	get_cmd(&cmd.path, arg);
	cmd.args = ft_split(arg, ' ');
	if (!cmd.args)
		error_exit(4, "Split failure");
	return (cmd);
}

void	build_cmd(t_cmd *cmd_1, t_cmd *cmd_2, char *arg_1, char *arg_2)
{
	*cmd_1 = param_split(arg_1);
	*cmd_2 = param_split(arg_2);
}
