/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2021/12/16 16:43:27 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(int fd, char *cmd)
{
	int	ln;
	int	i;

	i = 0;
	ln = 1;
	while (cmd[i] == ECHO[i])
		i++;
	i++;
	if (cmd[i] == '-' && cmd[i + 1] == 'n')
	{
		ln = 0;
		i += 2;
	}
	while (cmd[i] && cmd[i] == ' ')
		i++;
	if (ln)
		putstr_endl(fd, cmd + i);
	else
		putstr(fd, cmd + i);
	add_history(cmd);
}

void	cmd_pwd(int fd)
{
	char	path[PATH_BUF];

	if (path != NULL)
		putstr_endl(fd, getcwd(path, PATH_BUF));
	add_history(PWD);
}

void	cmd_env(int fd, t_env g_env)
{
	int	i;

	i = -1;
	while (g_env.var_env[++i])
		putstr_endl(fd, g_env.var_env[i]);
	add_history(ENV);
}

void	cmd_cd(int fd, t_env *g_env, char *cmd)
{
	(void) g_env;
	(void) cmd;
}
