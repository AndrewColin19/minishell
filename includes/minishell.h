/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:20 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 17:40:53 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

# define SHELL_TEXT "minishell$ "
# define ECHO "echo"
# define PWD "pwd"
# define CD "cd"
# define ENV "env"
# define EXPORT "export"
# define UNSET "unset"
# define EXIT "exit"

typedef struct s_env
{
	int		size_env;
	int		status;
	char	**var_env;
}	t_env;

typedef struct s_redir
{
	char			*kw;
	int				type;
	struct s_redir	*next;
}				t_redir;

typedef struct s_cmd
{
	char	*cmd;
	char	*kw;
	char	**args;
	t_redir	**redirections;
}				t_cmd;

typedef struct s_line
{
	char	*line;
	t_cmd	**cmds;
}				t_line;

extern t_env	g_env;

t_line	**parse(char *cmd);
int		check_cmd(char *cmd, char *kw, int op);
int		is_only_n(char *cmd);
void	exec(t_cmd **cmds, int i, int in);
void	free_lines(t_line **cmd);
/*-------------utils------------*/
char	**ft_split(const char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split_mod(const char *s, char c);
void	*ft_calloc(size_t nmemb, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
int		ft_str_contain(char *substr, char *str);
int		ft_isalnum(int c);
int		ft_isascii(int c);
int		ft_isbackslashable(int c);
int		check_pip(char *cmd);
char	*get_char(char *cmd, size_t start, size_t end);
char	*ft_itoa(int n);
/*--------------del--------------*/
void	ft_rm_space_start(char **cmd_tab);
void	remove_quote(char *cmd, char quote);
void	del_quote(char *cmd);
void	rm_char(char *str, size_t index);
void	remove_backslash(char *str);
void	remove_backslash_in_quote(char *str, char quote);
/*-------------write------------*/
void	putstr(int fd, char *s);
void	putstr_endl(int fd, char *s);
void	put_error(char *er, char *cmd);
/*-------------frees------------*/
void	free_cmds(char **cmd);
/*--------------env-------------*/
char	*get_var_env(char *kw);
int		add_var_env(char *kw, char *value);
void	init(char **ev);
int		set_var_env(char *kw, char *value);
void	expend_var(char **cmd, size_t index);
void	expend_var_quote(char **cmd, size_t *i, char quote);
void	expend_all(t_cmd **cmd);
void	expend(char **cmd);
void	aff_export(int fd);
/*--------------fct-------------*/
void	cmd_echo(int fd, t_cmd *cmd);
void	cmd_pwd(int fd);
void	cmd_env(int fd);
void	cmd_exec(t_cmd *cmd, int in, int out);
void	cmd_cd(t_cmd *cmd);
void	cmd_export(int fd, t_cmd *cmd);
void	cmd_unset(t_cmd *cmd);
void	cmd_exit();
char	*read_result(int fd);
/*--------------redirection------*/
int		write_redirection(int input, int fd);
int		check_redirection_o(char **cmd);
int		check_redirection_i(char **cmd);
void	delete_redirection(char **cmd, char c);
int		read_file(t_redir *r);
int		heredoc(t_redir *r);
int		inc_i(char *cmd, char c);
char	*get_kw(char *cmd, char type);
t_redir	*get_redirection(char **cmd, int i);
int		get_redirect(t_redir **redir, int *in, int *out);
int		ft_create_file(t_redir *redir);
void	rl_replace_line(const char *text, int clear_undo);

#endif