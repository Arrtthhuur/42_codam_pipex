/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:59:39 by abeznik       #+#    #+#                 */
/*   Updated: 2022/03/21 12:55:19 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // EXIT_
# include <stddef.h> // size_t

# define CHILD 0
# define SUCCESS 0
# define FAILURE -1
# define WRITE 1
# define READ 0

typedef struct s_cmd
{
	char	*cmd;
	char	*path;
	char	**args;
}	t_cmd;

/*
** Main functions.
*/
char	*path_build(t_cmd cmd, char **envp);
void	cmd_get(t_cmd *cmd, char *arg);
int		main(int argc, char **argv, char **envp);
void	files_open(int fd[2], char *file1, char *file2);
void	input_parse(t_cmd *cmd1, t_cmd *cmd2, char *arg1, char *arg2);
// int		pipex(int fd[2], t_cmd *cmd1, t_cmd *cmd2, char **envp);
int		pipex(char **argv, t_cmd *cmd1, t_cmd *cmd2, char **envp);

/*
** wrapper.c
*/
void	perror_wrap(char *msg);
void	dup2_wrap(int fd1, int fd2);
int		fork_wrap(void);
int		pipe_wrap(void);

/*
** exit_message.c
*/
int		error_msg(char *msg);
int		success_msg(char *msg);
void	error_exit(int error_code, char *msg);

/*
** Util functions.
*/
void	free_split(char **split);
void	*ft_memcpy(void *dst, void *src, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif