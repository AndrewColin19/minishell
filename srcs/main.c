/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2021/12/16 14:26:14 by acolin           ###   ########.fr       */
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
		if (ft_strncmp(cmds[i], ECHO, ft_strlen(ECHO)) == 0 && cmds[i][ft_strlen(ECHO)] == ' ')
			cmd_echo(cmds[i]);
		else if (ft_strncmp(cmds[i], PWD, ft_strlen(cmds[i])) == 0)
			cmd_pwd();
		else if (ft_strncmp(cmds[i], ENV, ft_strlen(cmds[i])) == 0)
			cmd_env(g_env);
		else
			cmd_exec(cmds[i], g_env.var_env);
	}
}

int	main(int argc, char *argv[], char **ev)
{
	char	**cmds;

	(void) argc;
	(void) argv;
	g_env.var_env = ev;
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
