/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:59:39 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/11 16:04:06 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // EXIT_
# include <stddef.h> // size_t

# define CHILD 0
# define SUCCESS 0
# define ERROR -1

typedef struct s_cmd
{
	char	*path;
	char	**args;
}	t_cmd;

int		main(int argc, char **argv, char **envp);
void	open_files(int fd[2], char *file1, char *file2);
int		build_cmd(t_cmd cmd1, t_cmd cmd2, char **argv);
char	*get_cmd(t_cmd cmd, char **argv, char **envp);
int		pipex(int fd1, int fd2, t_cmd cmds[2], char **envp);

/*
** Util functions.
*/
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, void *src, size_t n);
char	*ft_strdup(const char *s1);

/*
** Exit succes or error message.
*/
int		error_msg(char *msg);
int		success_msg(char *msg);
void	error_exit(int error_code, char *msg);

#endif