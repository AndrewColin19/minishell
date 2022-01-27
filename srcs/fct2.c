/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:39:08 by acolin            #+#    #+#             */
/*   Updated: 2022/01/27 14:37:24 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_unset(t_cmd *cmd)
{
	int		i;
	size_t	size;

	if (get_var_env(cmd->args[1]))
	{
		i = 0;
		size = ft_strlen(cmd->args[1]);
		while (ft_strncmp(cmd->args[1], g_env.var_env[i], size) != 0)
			i++;
		if (g_env.var_env[i])
			free(g_env.var_env[i]);
		while (g_env.var_env[i])
		{
			g_env.var_env[i] = g_env.var_env[i + 1];
			i++;
		}
		g_env.size_env -= 1;
		g_env.status = 0;
	}
}

void	cmd_exit(t_line **lines)
{
	printf("exit\n");
	free_lines(lines);
	exit(1);
}
