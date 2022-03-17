/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_input.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/13 12:34:24 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/17 14:39:42 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h>

static void	print_cmd(t_cmd cmd)
{
	int	i;

	i = 0;
	write(2, "printing\n", 10);
	while (cmd.args[i])
	{
		write(2, cmd.args[i], ft_strlen(cmd.args[i]));
		write(2, "\n", 1);
		i++;
	}
}

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
** Split parameters of the args.
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
	print_cmd(cmd);
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
