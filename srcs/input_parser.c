/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input_parser.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/11 15:56:58 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/11 16:12:12 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <stdio.h> // printf

int	build_cmd(t_cmd cmd1, t_cmd cmd2, char **argv)
{
	// cmd1.args = NULL;
	printf("%s and %s\n", argv[2], argv[3]);
	printf("%s\n", cmd1.args[0]);
	// cmd1.args[0] = argv[2];
	// cmd2.args[0] = argv[3];
	// printf("%s and %s\n", cmd1.args[0], cmd2.args[0]);
	return (0);
}
