/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:34:54 by acolin            #+#    #+#             */
/*   Updated: 2021/12/09 11:59:46 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	ft_split_sep(char c, char sep)
{
	return (c == sep || c == '\0');
}

static int	ft_split_search(const char *s, char c)
{
	int		j;

	j = 0;
	while (!ft_split_sep(s[j], c))
		j++;
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
		if (!ft_split_sep(s[i], c) && ft_split_sep(s[i + 1], c))
		{
			size++;
		}
		i++;
	}
	return (size);
}

static char	*ft_split_copy(const char *s, int start, int size)
{
	char	*word;
	int		i;

	word = (char *) ft_calloc(size + 1, 1);
	i = 0;
	while (i < size)
	{
		word[i] = s[start + i];
		i++;
	}
	return (word);
}

/**
 * Alloue (avec malloc(3)) et retourne un tableau
 * de chaines de caracteres obtenu en séparant ’s’ à
 * l’aide du caractère ’c’, utilisé comme délimiteur.
 * Le tableau doit être terminé par NULL.
 *
 * \param	*s	La chaine de caractères à découper.
 * \param	c	Le caractère délimitant.
 * \return		Le tableau de nouvelles chaines de caractères,
 * 				résultant du découpage. NULL si l’allocation
 * 				échoue.
 */
char	**ft_split(const char *s, char c)
{
	char	**words;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	words = (char **) malloc(sizeof(char *) * (ft_split_size(s, c) + 1));
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
			words[k++] = ft_split_copy(s, i, j);
			i += j;
		}
	}
	words[k] = NULL;
	return (words);
}
