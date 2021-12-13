/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:20 by acolin            #+#    #+#             */
/*   Updated: 2021/12/11 15:55:09 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>

# define PATH_BUF 4096

# define SHELL_TEXT "minishell$ "
# define ECHO "echo"
# define PWD "pwd"

char	**parse(char *cmd);
/*-------------uitls------------*/
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
/*-------------write------------*/
void	putstr(int fd, char *s);
void	putstr_endl(int fd, char *s);
/*-------------frees------------*/
void	free_cmds(char **cmd);
/*--------------fct-------------*/
void	cmd_echo(char **cmd);
void cmd_pwd(char *path);

#endif