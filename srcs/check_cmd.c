/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:56:28 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 10:01:08 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_only_n(char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i] == 'n')
		i++;
	if (cmd[i] != ' ' && cmd[i] != '\0')
		return (0);
	return (1);
}

int	check_cmd(char *cmd, char *kw, int op)
{
	int	kw_size;
	int	i;

	kw_size = ft_strlen(kw);
	i = -1;
	while (++i < kw_size)
	{
		if (cmd[i] != kw[i])
			return (0);
	}
	if (cmd[i] != ' ' && cmd[i] != '\0')
		return (0);
	while (cmd[i++] != '\0')
	{
		if (cmd[i] == '-' && cmd[i - 1] == ' ' && cmd[i + 1] != ' ' && !op)
			return (0);
	}
	return (1);
}
