/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 10:35:27 by lmataris          #+#    #+#             */
/*   Updated: 2022/01/26 17:43:17 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	int		exp;

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

int	inc_i(char *cmd, char c)
{
	int		i;
	char	quote;

	i = 0;
	while (cmd[i] && cmd[i] != c)
	{
		if ((cmd[i] == '\'' || cmd[i] == '\"'))
		{
			if (cmd[i - 1] != '\\')
			{
				quote = cmd[i];
				i++;
				while (cmd[i] && cmd[i] != quote)
				{
					if (cmd[i] == quote && cmd[i - 1] != '\\')
						break ;
					else
						i++;
				}
			}
		}
		i++;
	}
	return (i);
}

void	delete_redirection(char **cmd, char c)
{
	int		i;
	int		j;
	int		nb_char;

	i = inc_i(cmd[0], c);
	j = i;
	while ((cmd[0][j] == c || cmd[0][j] == ' ') && cmd[0][j])
		j++;
	while (cmd[0][j] != ' ' && cmd[0][j])
		j++;
	while (cmd[0][j] == ' ' && cmd[0][j])
		j++;
	nb_char = j - i;
	while (nb_char--)
	{
		j = i;
		while (cmd[0][j])
		{
			cmd[0][j] = cmd[0][j + 1];
			j++;
		}
	}
}
