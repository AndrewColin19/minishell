/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2021/12/15 15:19:45 by acolin           ###   ########.fr       */
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

void	cmd_pwd(char *path)
{
	if (path != NULL)
		printf("%s\n", path);
	add_history(PWD);
}