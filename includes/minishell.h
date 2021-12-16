/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:20 by acolin            #+#    #+#             */
/*   Updated: 2021/12/16 16:28:01 by acolin           ###   ########.fr       */
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
# define CMD_PATH "/bin/"

typedef struct s_env
{
	char	path[PATH_BUF];
	char	**var_env;
}	t_env;

char	**parse(char *cmd);
int		check_cmd(char *cmd, char *kw, int op);
/*-------------uitls------------*/
char	**ft_split(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
/*-------------write------------*/
void	putstr(int fd, char *s);
void	putstr_endl(int fd, char *s);
void	put_error(char *er, char *cmd);
/*-------------frees------------*/
void	free_cmds(char **cmd);
/*--------------fct-------------*/
void	cmd_echo(int fd, char *cmd);
void	cmd_pwd(void);
void	cmd_env(t_env g_env);
void	cmd_exec(char *cmd, char **env);

#endif