/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:57:41 by acolin            #+#    #+#             */
/*   Updated: 2022/01/08 01:06:07 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_rm_space_start(char **cmd_tab)
{
	int	i;
	int	j;

	if (!cmd_tab)
		return ;
	i = 0;
	while (cmd_tab[i])
	{
		if (cmd_tab[i][0] == ' ')
		{
			j = 0;
			while (cmd_tab[i][j])
			{
				cmd_tab[i][j] = cmd_tab[i][j + 1];
				j++;
			}
		}
		i++;
	}
}

void	remove_quote(char *cmd, char quote)
{
	int	as_quote;
	int	i;

	i = 0;
	as_quote = 1;
	while (as_quote != 0)
	{
		as_quote = 0;
		i = 0;
		while (cmd[i] != '\0' && cmd[i] != quote)
			i++;
		if (cmd[i] == quote)
		{
			while (cmd[i] != '\0')
			{
				cmd[i] = cmd[i + 1];
				i++;
			}
			as_quote = 1;
		}
		else
			as_quote = 0;
	}
}
