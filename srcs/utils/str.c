/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmataris <lmataris@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 14:25:54 by acolin            #+#    #+#             */
/*   Updated: 2022/01/05 14:41:24 by lmataris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*sa;
	unsigned char	*sb;
	size_t			i;

	if (n == 0)
		return (0);
	sa = (unsigned char *) s1;
	sb = (unsigned char *) s2;
	i = 0;
	while (sa[i] == sb[i] && sa[i] != '\0' && sb[i] != '\0' && i < n - 1)
		i++;
	return (sa[i] - sb[i]);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	s1_size;

	if (!s1 || !s2)
		return (NULL);
	s1_size = ft_strlen(s1);
	str = malloc(sizeof(char) * (s1_size + ft_strlen(s2)) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[s1_size + i] = s2[i];
		i++;
	}
	str[s1_size + i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int     ft_str_contain(char *substr, char *str)
{
	int 	i;
	char	quote;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && str[i - 1] != '\\')
		{
			quote = str[i];
			i++;
			while (str[i] && str[i] != quote && str[i - 1] != '\\')
				i++;
		}
		if (!ft_strncmp(str + i, substr, ft_strlen(substr)))
			return (1);
		i++;
	}
	return (0);
}