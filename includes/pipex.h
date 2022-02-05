/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: abeznik <abeznik@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/11/29 14:59:39 by abeznik       #+#    #+#                 */
/*   Updated: 2022/02/05 13:30:15 by abeznik       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h> // EXIT_
# include <stddef.h> // size_t

# define CHILD 0
# define SUCCESS 0
# define ERROR -1

int		main(int argc, char **argv);
void	open_files(int fd1, char *file1, int fd2, char *file2);

/*
** Util functions.
*/
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

/*
** Exit succes or error message.
*/
int		error_msg(char *msg);
int		success_msg(char *msg);
void	error_exit(int error_code, char *msg);

#endif