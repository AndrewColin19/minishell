/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:35:54 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 10:17:59 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_split_sep(char c, char sep);

static int	ignore_quote(const char *s, int *i, char quote)
{
	(*i)++;
	while (1)
	{
		if (s[*i] == '\\')
			(*i) += 2;
		if (s[*i] == quote)
			break ;
		if (s[*i] == '\0')
			break ;
		(*i)++;
	}
	if (s[*i] == '\0')
		return (0);
	return (1);
}

static int	ft_split_search(const char *s, char c)
{
	int		j;

	j = 0;
	while (s[j])
	{
		if (s[j] == '"' && s[j - 1] != '\\')
			ignore_quote(s, &j, '"');
		if (s[j] == '\'' && s[j - 1] != '\\')
			ignore_quote(s, &j, '\'');
		if (ft_split_sep(s[j], c))
			return (j);
		j++;
	}
	return (j);
}

static int	ft_split_size(const char *s, char c)
{
	int		size;
	int		i;

	size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && s[i - 1] != '\\')
		{
			if (!ignore_quote(s, &i, '\''))
				return (-1);
		}
		if (s[i] == '"' && s[i - 1] != '\\')
		{
			if (!ignore_quote(s, &i, '"'))
				return (-1);
		}
		if (!ft_split_sep(s[i], c) && ft_split_sep(s[i + 1], c))
			size++;
		i++;
	}
	return (size);
}

static char	*ft_split_copy(const char *s, int start, int size)
{
	char	*word;
	int		i;

	word = ft_calloc(size + 1, 1);
	i = 0;
	while (i < size)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split_mod(const char *s, char c)
{
	char	**words;
	int		i;
	int		j;
	int		k;

	if (ft_split_size(s, c) == -1)
		return (NULL);
	words = malloc(sizeof(char *) * (ft_split_size(s, c) + 1));
	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else
		{
			j = ft_split_search(s + i, c);
			words[k] = ft_split_copy(s, i, j);
			i += j;
			k++;
		}
	}
	words[k] = NULL;
	return (words);
}
