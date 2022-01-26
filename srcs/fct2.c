/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:39:08 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 17:50:35 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_unset(t_env *env, t_cmd *cmd)
{
	(void) env;
	(void) cmd;
}

void	cmd_exit(t_line **lines)
{
	printf("exit\n");
	free_lines(lines);
	exit(1);
}