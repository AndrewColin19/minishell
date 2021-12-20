/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2021/12/20 15:56:10 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	g_env;

void	exec(char **cmds)
{
	int		i;

	i = -1;
	while (cmds[++i])
	{
		if (check_cmd(cmds[i], ECHO, 1))
			cmd_echo(0, cmds[i]);
		else if (check_cmd(cmds[i], PWD, 0))
			cmd_pwd(0, &g_env);
		else if (check_cmd(cmds[i], ENV, 0))
			cmd_env(0, g_env);
		else if (check_cmd(cmds[i], CD, 0))
			cmd_cd(&g_env, cmds[i]);
		else
			cmd_exec(cmds[i], g_env.var_env);
	}
}

int	main(int argc, char *argv[], char **ev)
{
	char	**cmds;

	(void) argc;
	(void) argv;
	init(ev, &g_env);
	while (1)
	{
		cmds = parse(readline(SHELL_TEXT));
		if (cmds == NULL)
		{
			printf("Error\n");
			free_cmds(cmds);
		}
		else
			exec(cmds);
	}
}
