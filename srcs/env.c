/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:45:14 by acolin            #+#    #+#             */
/*   Updated: 2021/12/16 16:55:05 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_env(t_env *env, char *kw)
{
	int		i;
	int		j;
	int		s_kw;
	char	*value;

	i = -1;
	s_kw = ft_strlen(kw);
	while (++i < env->size_env)
	{
		j = 0;
		if (env->var_env[i][j] == kw[j])
		{
			while (env->var_env[i][j] == kw[j])
			{
				if (j + 1 == s_kw)
					return (env->var_env[i] + j);
				j++;
			}
		}
	}
	return (NULL);
}

void	init(char **ev, t_env *env)
{
	int i;

	while (ev[i])
		i++;
	env->var_env = ev;
	env->size_env = i;	
}
