/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:47:47 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/31 15:21:40 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // access

/*
** Test out all paths with access.
*/
static char	*path_access(char **env_p, t_cmd cmd)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env_p[i])
	{
		tmp = ft_strjoin(env_p[i], cmd.cmd);
		if (!tmp)
			error_exit(5, "ft_strjoin access");
		if (access(tmp, X_OK) == SUCCESS)
		{
			cmd.path = tmp;
			return (cmd.path);
		}
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (cmd.cmd);
}

/*
** Split all paths env variable and add "/".
*/
static char	**path_split(char *path)
{
	char	**env_paths;
	char	*tmp;
	int		i;

	env_paths = ft_split(path + 5, ':');
	if (!env_paths)
		error_exit(3, "ft_split path");
	i = 0;
	while (env_paths[i])
	{
		tmp = ft_strjoin(env_paths[i], "/");
		if (!tmp)
			error_exit(5, "ft_strjoin split");
		free(env_paths[i]);
		env_paths[i] = tmp;
		i++;
	}
	return (env_paths);
}

/*
** Find path environment variable.
*/
static char	*path_find(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
		i++;
	}
	return (NULL);
}

/*
** Build path of command.
** Step 1: Test path with access
** Step 2: Find PATH env variable
** Step 3: Split paths in PATH and add trailing "/"
** Step 4: Test different paths with access
*/
char	*path_build(t_cmd *cmd, char **envp)
{
	char	*path_var;
	char	**env_paths;

	if (cmd->cmd == NULL)
		return (NULL);
	if (access(cmd->cmd, X_OK) == SUCCESS)
		return (cmd->cmd);
	path_var = path_find(envp);
	if (!path_var)
		return (NULL);
	env_paths = path_split(path_var);
	if (!env_paths)
		return (NULL);
	cmd->path = path_access(env_paths, *cmd);
	if (!cmd->path)
		return (NULL);
	free_grid(env_paths);
	return (cmd->path);
}
