/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_cmd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/13 12:34:24 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/16 12:43:46 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h> // printf

void	print_args(t_cmd cmd)
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

void	build_cmd(t_cmd *cmd1, t_cmd *cmd2, char *arg1, char *arg2)
{
	*cmd1 = param_split(arg1);
	*cmd2 = param_split(arg2);
	print_args(*cmd1);
	print_args(*cmd2);
}
