/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:45:14 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 14:15:58 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*set_value(char *kw, char *value)
{
	char	*v;
	int		size_kw;
	int		size_v;
	int		i;
	int		j;

	size_kw = ft_strlen(kw);
	size_v = ft_strlen(value);
	v = malloc(sizeof(char) * size_kw + size_v + 2);
	i = -1;
	j = -1;
	while (++i < size_kw)
		v[i] = kw[i];
	if (value != NULL)
	{
		v[i] = '=';
		while (++j < size_v)
			v[++i] = value[j];
	}
	v[++i] = '\0';
	return (v);
}

int	add_var_env(t_env *env, char *kw, char *value)
{
	char	**var;
	int		i;

	if (get_var_env(env, kw))
		return (set_var_env(env, kw, value));
	env->size_env += 1;
	var = malloc(sizeof(char *) * env->size_env + 1);
	i = 0;
	while (env->var_env[i])
	{
		var[i] = ft_strdup(env->var_env[i]);
		i++;
	}
	var[i] = set_value(kw, value);
	var[++i] = NULL;
	env->var_env = var;
	return (1);
}

int	set_var_env(t_env *env, char *kw, char *value)
{
	int		i;
	int		j;
	int		s_kw;

	i = -1;
	s_kw = ft_strlen(kw);
	while (++i < env->size_env)
	{
		j = 0;
		if (env->var_env[i][j] == kw[j])
		{
			while (env->var_env[i][j] == kw[j])
			{
				if (j == s_kw - 1)
				{
					env->var_env[i] = set_value(kw, value);
					return (1);
				}
				j++;
			}
		}
	}
	return (0);
}

char	*get_var_env(t_env *env, char *kw)
{
	int		i;
	int		j;
	int		s_kw;

	i = -1;
	s_kw = ft_strlen(kw);
	while (++i < env->size_env)
	{
		j = 0;
		if (env->var_env[i][j] == kw[j])
		{
			while (env->var_env[i][j] == kw[j])
			{
				if ((j == s_kw - 1 && env->var_env[i][j + 1] == '=') || env->var_env[i][j + 1] == '\0')
					return (env->var_env[i] + j + 2);
				j++;
			}
		}
	}
	return (NULL);
}

void	init(char **ev, t_env *env)
{
	int		i;

	i = 0;
	while (ev[i])
		i++;
	env->var_env = malloc(sizeof(char *) * i);
	env->size_env = i;
	i = -1;
	while (ev[++i])
		env->var_env[i] = ft_strdup(ev[i]);
	env->var_env[i] = NULL;
}
