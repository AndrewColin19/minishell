/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2021/12/16 15:18:05 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(char *cmd)
{
	int	ln;

	ln = 1;
	if (cmd[5] == '-' && cmd[6] == 'n' && cmd[7] == ' ')
		ln = 0;
	if (ln)
	{
		putstr(0, cmd + 5);
		write(0, "\n", 1);
	}
	else
		putstr(0, cmd + 8);
	add_history(cmd);
}

void	cmd_pwd()
{
	char	path[PATH_BUF];

	if (path != NULL)
		printf("%s\n", getcwd(path, PATH_BUF));
	add_history(PWD);
}

void	cmd_env(t_env g_env)
{
	int i;

	i = -1;
	while (g_env.var_env[++i])
		printf("%s\n", g_env.var_env[i]);
	add_history(ENV);
}

void cmd_cd(t_env *g_env, char *cmd)
{
	(void) g_env;
	(void) cmd;
}