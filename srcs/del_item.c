/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:57:41 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 10:01:46 by lmataris         ###   ########.fr       */
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

void	rm_char(char *str, size_t index)
{
	while (str[index])
	{
		str[index] = str[index + 1];
		index++;
	}
}

void	skip(char *str, size_t *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	while (str[*i] != c)
		(*i)++;
	(*i)++;
}

void	remove_backslash_in_quote(char *str, char quote)
{
	size_t	i;

	(void) quote;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			skip(str, &i);
		i++;
		if (str[i] == '\\')
			rm_char(str, i);
	}
}

void	remove_backslash(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
			skip(str, &i);
		if (str[i] == '\'')
			skip(str, &i);
		if (str[i] == '\\')
			rm_char(str, i--);
		i++;
	}
}
