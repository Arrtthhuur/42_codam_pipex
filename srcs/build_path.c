/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   build_path.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:47:47 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/19 15:27:21 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // access

static char	*path_access(char **env_p, char *path)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env_p[i])
	{
		tmp = ft_strjoin(env_p[i], path);
		if (!tmp)
			error_exit(5, "ft_strjoin access");
		if (access(tmp, X_OK) == SUCCESS)
			return (tmp);
		i++;
	}
	return (NULL);
}

static char	**path_split(char *path)
{
	char	**env_paths;
	int		i;

	env_paths = ft_split(path + 5, ':');
	if (!env_paths)
		error_exit(3, "ft_split path");
	i = 0;
	while (env_paths[i])
	{
		env_paths[i] = ft_strjoin(env_paths[i], "/");
		if (!env_paths[i])
			error_exit(5, "ft_strjoin split");
		i++;
	}
	return (env_paths);
}

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

char	*path_build(t_cmd cmd, char **envp)
{
	char	*path_var;
	char	**env_paths;
	char	*cmd_path;

	if (access(cmd.path, X_OK) == SUCCESS)
		return (cmd.path);
	path_var = path_find(envp);
	env_paths = path_split(path_var);
	cmd_path = path_access(env_paths, cmd.path);
	return (cmd_path);
}