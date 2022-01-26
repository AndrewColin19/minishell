/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2022/01/26 14:07:10 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(int fd, char *cmd)
{
	int		i;
	int		ln;

	del_quote(cmd);
	i = ft_strlen(ECHO) + 1;
	ln = 1;
	if (cmd[i] == '-' && is_only_n(cmd + i + 1))
		ln = 0;
	if (ln)
		putstr_endl(fd, cmd + i);
	else
	{
		while (cmd[i] && cmd[i] != ' ')
			i++;
		putstr(fd, cmd + i);
	}
}

void	cmd_pwd(int fd, t_env *env)
{
	char	*path;

	path = get_var_env(env, "PWD");
	if (path != NULL)
		putstr_endl(fd, path);
}

void	cmd_env(int fd, t_env g_env)
{
	int	i;

	i = -1;
	while (g_env.var_env[++i])
		putstr_endl(fd, g_env.var_env[i]);
}

void	cmd_cd(t_env *g_env, t_cmd *cmd)
{
	int		i;
	char	*path;

	i = 0;
	if (cmd->args[1] == NULL)
		path = get_var_env(g_env, "HOME");
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		putstr(1, "cd: ");
		perror(path);
	}
	else
	{
		add_var_env(g_env, "OLDPWD", get_var_env(g_env, "PWD"));
		set_var_env(g_env, "PWD", path);
	}
}

void	cmd_export(int fd, t_env *g_env, char *cmd)
{
	size_t	i;
	size_t	j;

	del_quote(cmd);
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	while (cmd[i] == ' ')
		i++;
	if (cmd[i] == '\0')
		aff_export(fd, g_env);
	else
	{
		j = i;
		while (cmd[j] && cmd[j] != '=')
			j++;
		if (cmd[j] == '\0')
			add_var_env(g_env, cmd + i, NULL);
		else
			add_var_env(g_env, get_char(cmd, i, j), cmd + j + 1);
	}
}
