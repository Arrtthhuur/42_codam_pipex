/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_command.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/10 12:47:47 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/11 15:49:21 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

#include <unistd.h> // access
#include <stdio.h>

// char	*path_join(char **envp, char *argv)
// {
	
// }

char	*path_access(char **env_p, char *argv)
{
	char	*tmp;
	int		i;

	i = 0;
	while (env_p[i])
	{
		tmp = ft_strjoin(env_p[i], argv);
		if (!tmp)
			error_exit(5, "Strjoin access");
		if (access(tmp, X_OK) == SUCCESS)
			return (tmp);
		i++;
	}
	return (NULL);
}

char	**path_split(char *path)
{
	char **env_paths;
	int i;

	env_paths = ft_split(path + 5, ':');
	if (!env_paths)
		error_exit(4, "Split");
	i = 0;
	while (env_paths[i])
	{
		env_paths[i] = ft_strjoin(env_paths[i], "/");
		// printf("%s\n", env_paths[i]);
		if (!env_paths[i])
			error_exit(4, "Strjoin split");
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

char	*get_cmd(t_cmd cmd, char **argv, char **envp)
{
	char	*path_var;
	char	**env_paths;
	char	*file_path;

	if (access(argv[2], X_OK) == SUCCESS)
	{
		cmd.path = argv[2];
		return (cmd.path);
	}
	path_var = path_find(envp);
	env_paths = path_split(path_var);
	file_path = path_access(env_paths, argv[2]);
	return (file_path);
}
