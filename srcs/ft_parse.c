/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:19:11 by acolin            #+#    #+#             */
/*   Updated: 2021/12/09 15:29:32 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pip(char *cmd)
{
	int		i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '|' && cmd[i + 1] == '|' && cmd[i + 2] == '|')
			return (0);
		if (cmd[i] == '&' && cmd[i + 1] == '&' && cmd[i + 2] == '&')
			return (0);
	}
	return (1);
}

void	ft_rm_space_start(char **cmd_tab)
{
	int	i;
	int	j;

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

int	parse(char *cmd)
{
	char	**cmd_tab;
	
	if (!check_pip(cmd))
		return (0);
	cmd_tab = ft_split(cmd, '|');
	ft_rm_space_start(cmd_tab);
	return (1);
}