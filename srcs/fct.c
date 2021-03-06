/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2022/01/27 14:58:52 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(int fd, t_cmd *cmd)
{
	int		i;
	int		ln;

	ln = 0;
	if (cmd->args[1] && cmd->args[1][0] == '-' && is_only_n(cmd->args[1] + 1))
		ln = 1;
	i = 1 + ln;
	while (cmd->args[i])
	{
		putstr(fd, cmd->args[i]);
		if (cmd->args[i + 1] != NULL)
			putstr(fd, " ");
		i++;
	}
	if (!ln)
		putstr(fd, "\n");
}

void	cmd_pwd(int fd)
{
	char	*path;

	path = get_var_env("PWD");
	if (path != NULL)
		putstr_endl(fd, path);
	g_env.status = 0;
}

void	cmd_env(int fd)
{
	int	i;
	int	j;

	i = -1;
	while (g_env.var_env[++i])
	{
		j = 0;
		while (g_env.var_env[i][j])
		{
			if (g_env.var_env[i][j] == '=')
			{
				putstr_endl(fd, g_env.var_env[i]);
				break ;
			}
			j++;
		}		
	}
	g_env.status = 0;
}

void	cmd_cd(t_cmd *cmd)
{
	char	*path;

	if (cmd->args[1] == NULL)
		path = get_var_env("HOME");
	else
		path = cmd->args[1];
	if (chdir(path) == -1)
	{
		putstr(1, "cd: ");
		perror(path);
		g_env.status = 1;
	}
	else
	{
		add_var_env(ft_strdup("OLDPWD"), get_var_env("PWD"));
		set_var_env(ft_strdup("PWD"), path);
	}
	g_env.status = 0;
}

void	cmd_export(int fd, t_cmd *cmd)
{
	size_t	i;

	if (cmd->args[1] == NULL)
		aff_export(fd);
	else
	{
		i = 0;
		while (cmd->args[1][i] && cmd->args[1][i] != '=')
		{
			if (!ft_isok(cmd->args[1]))
			{
				printf("%s: '%s': not a valid identifier\n",
					cmd->kw, cmd->args[1]);
				g_env.status = 1;
				return ;
			}
			i++;
		}
		if (cmd->args[1][i] == '\0')
			add_var_env(ft_strdup(cmd->args[1]), NULL);
		else
			add_var_env(get_char(cmd->args[1], 0, i),
				cmd->args[1] + i + 1);
		g_env.status = 0;
	}
}
