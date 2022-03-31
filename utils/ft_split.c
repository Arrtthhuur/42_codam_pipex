/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/15 09:15:26 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/31 12:57:51 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static	int	count_pointers(char const *s, char c)
{
	unsigned int	i;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s != c && *s)
			i++;
		while (*s != c && *s)
			s++;
	}
	return (i);
}

static	char	**free_arrays(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

static	char	**fill_grid(char const *s, char c, char **ret, unsigned int i)
{
	unsigned int	j;
	unsigned int	k;

	k = 0;
	while (*s)
	{
		j = 0;
		while (*s == c)
			s++;
		while (s[j] != c && s[j] != '\0')
			j++;
		if (k < i)
		{
			ret[k] = ft_substr(s, 0, j);
			if (!ret[k])
				return (free_arrays(ret, k));
		}
		k++;
		while (*s != c && *s)
			s++;
	}
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	char			**ret;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = count_pointers(s, c);
	ret = ft_calloc(sizeof(char *), i + 1);
	if (!ret)
		return (NULL);
	if (i == 0)
		return (ret);
	ret = fill_grid(s, c, ret, i);
	return (ret);
}
