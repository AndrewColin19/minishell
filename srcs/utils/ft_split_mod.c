/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_mod.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 14:35:54 by acolin            #+#    #+#             */
/*   Updated: 2022/01/05 16:28:57 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_split_sep(char c, char sep);

static int	ignore_quote(const char *s, int *i, char quote)
{
	(*i)++;
	while (s[*i] != quote && s[*i])
		(*i)++;
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
		if (s[j] == '"')
			ignore_quote(s, &j, '"');
		else if (s[j] == '\'')
			ignore_quote(s, &j, '\'');
		else if (ft_split_sep(s[j], c))
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
		if (s[i] == '\'')
		{
			if (!ignore_quote(s, &i, '\''))
				return (-1);
		}
		else if (s[i] == '"')
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
	if (!words)
		return (NULL);
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
