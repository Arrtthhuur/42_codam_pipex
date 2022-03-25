/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/13 12:34:24 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/24 16:57:57 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/*
** Clean parameters with single quotes.
** ex: sed 's/.../g'
*/
static void	param_clean(t_cmd cmd)
{
	int		i;
	int		x;
	char	*tmp;

	i = 0;
	while (cmd.args[i])
	{
		if (cmd.args[i][0] == 39)
		{
			x = 1;
			while (cmd.args[i][x] != 39)
				x++;
			tmp = ft_substr(cmd.args[i], 1, x - 1);
			if (!tmp)
			{
				free(tmp);
				error_exit(4, "ft_substr clean");
			}
			free(cmd.args[i]);
			cmd.args[i] = tmp;
		}
		i++;
	}
}

/*
** Get command path.
** Substr only the command, without the parameters.
*/
static void	cmd_get(t_cmd *cmd, char *arg)
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
	{
		free(cmd->path);
		error_exit(4, "ft_substr cmd");
	}
}

/*
** Split parameters of the args.
** print_cmd(cmd);
*/
static t_cmd	param_split(char *arg)
{
	t_cmd	cmd;

	cmd_get(&cmd, arg);
	cmd.args = ft_split(arg, ' ');
	if (!cmd.args)
	{
		free_split(cmd.args);
		error_exit(3, "ft_split param");
	}
	param_clean(cmd);
	return (cmd);
}

/*
** Separate cmd1 and cmd2.
*/
void	input_parse(t_cmd *cmd1, t_cmd *cmd2, char *arg1, char *arg2)
{
	*cmd1 = param_split(arg1);
	*cmd2 = param_split(arg2);
}
