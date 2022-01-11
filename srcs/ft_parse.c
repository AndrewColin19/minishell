/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:19:11 by acolin            #+#    #+#             */
/*   Updated: 2022/01/08 02:06:06 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rm_space_end(char **cmds)
{
	int		i;
	size_t	j;

	i = 0;
	while (cmds[i])
	{
		j = ft_strlen(cmds[i]) - 1;
		while (cmds[i][j] == ' ' && j > 0)
		{
			rm_char(cmds[i], j);
			j -= 1;
		}
		i++;
	}
}

void	expend(char **cmd)
{
	size_t	i;
	int	exp;

	i = 0;
	exp = 1;
	while (cmd[0][i])
	{
		if (cmd[0][i] == '"' && exp == 1)
			expend_var_quote(cmd, &i, cmd[0][i]);
		if (cmd[0][i] == '\'')
			exp = 0;
		if (cmd[0][i] == '$' && exp == 1)
			expend_var(cmd, i);
		if (cmd[0][i] == '\\')
			i++;
		i++;
	}
}

int	check_pip(char *cmd)
{
	size_t	i;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '|' && cmd[i + 1] == '|' && cmd[i + 2] == '|')
			return (0);
		if (cmd[i] == '&' && cmd[i + 1] == '&' && cmd[i + 2] == '&')
			return (0);
		if (cmd[i] == '\\' && cmd[i + 1] == '\0')
			return (0);
	}
	return (1);
}

void	del_quote(char *cmd)
{
	size_t i;
	char quote;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] == '"' && cmd[i - 1] != '\\') ||
			(cmd[i] == '\'' && cmd[i - 1] != '\\'))
		{
			quote = cmd[i];
			rm_char(cmd, i++);
			while (cmd[i] != quote)
			{
				if (cmd[i] == '\\')
					i++;
				i++;
			}
			rm_char(cmd, i);
		}
		i++;
	}
	remove_backslash(cmd);
}

char	**parse(char *cmd)
{
	char	**cmd_tab;
	size_t	i;

	add_history(cmd);
	if (!check_pip(cmd))
		return (NULL);
	cmd_tab = ft_split_mod(cmd, '|');
	if (!cmd_tab)
		return (NULL);
	ft_rm_space_start(cmd_tab);
	rm_space_end(cmd_tab);
	i = 0;
	while (cmd_tab[i])
		expend(&cmd_tab[i++]);
	return (cmd_tab);
}
