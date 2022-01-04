/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:20 by acolin            #+#    #+#             */
/*   Updated: 2021/12/20 16:13:56 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define PATH_BUF 4096

# define SHELL_TEXT "minishell$ "
# define ECHO "echo"
# define PWD "pwd"
# define CD "cd"
# define ENV "env"

typedef struct s_env
{
	int		size_env;
	char	**var_env;
}	t_env;

t_env	g_env;

char	**parse(char *cmd);
int		check_cmd(char *cmd, char *kw, int op);
/*-------------uitls------------*/
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
/*-------------write------------*/
void	putstr(int fd, char *s);
void	putstr_endl(int fd, char *s);
void	put_error(char *er, char *cmd);
/*-------------frees------------*/
void	free_cmds(char **cmd);
/*--------------env-------------*/
char	*get_var_env(t_env *env, char *kw);
int		add_var_env(t_env *env, char *kw, char *value);
void	init(char **ev, t_env *env);
int		set_var_env(t_env *env, char *kw, char *value);
/*--------------fct-------------*/
void	cmd_echo(int fd, char *cmd);
void	cmd_pwd(int fd, t_env *env);
void	cmd_env(int fd, t_env g_env);
void	cmd_exec(char *cmd, int in, int out);
void	cmd_cd(t_env *env, char *cmd);
char 	*read_result(int fd);

#endif