/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   find_path.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:47:47 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/14 15:49:36 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // access
#include <stdio.h>

char	*path_access(char **env_p, char *argv)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env_p[i])
	{
		tmp = ft_strjoin(env_p[i], argv);
		if (!tmp)
			error_exit(6, "Strjoin access");
		if (access(tmp, X_OK) == SUCCESS)
			return (tmp);
		i++;
	}
	return (NULL);
}

char	**path_split(char *path)
{
	char	**env_paths;
	int		i;

	env_paths = ft_split(path + 5, ':');
	if (!env_paths)
		error_exit(4, "Split");
	i = 0;
	while (env_paths[i])
	{
		env_paths[i] = ft_strjoin(env_paths[i], "/");
		if (!env_paths[i])
			error_exit(5, "Strjoin split");
		i++;
	}
	return (env_paths);
}

char	*path_find(char **envp)
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
	char	*file_path;

	if (access(cmd.path, X_OK) == SUCCESS)
		return (cmd.path);
	path_var = path_find(envp);
	env_paths = path_split(path_var);
	file_path = path_access(env_paths, cmd.path);
	return (file_path);
}

// void	get_path(t_cmd *cmd1, t_cmd *cmd2, char **argv, char **envp)
// {
// 	cmd1->path = path_build(*cmd1, envp);
// 	cmd2->path = path_build(*cmd2, envp);
// }
