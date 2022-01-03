/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:52:01 by acolin            #+#    #+#             */
/*   Updated: 2022/01/03 17:06:27 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_kw(char *cmd, size_t start, size_t end)
{
	char	*kw;
	size_t		i;
	
	kw = malloc(end - start + 1);
	if (!kw)
		return (NULL);
	i = 0;
	while (start++ < end)
		kw[i++] = cmd[start];
	return (kw);
}

void	replace_var(char **cmds, size_t index, char *var, size_t start)
{
	char	*cmd;
	char	*ncmd;
	size_t		j;
	size_t		i;

	cmd = ft_strdup(cmds[index]);
	free(cmds[index]);
	ncmd = ft_calloc(1, ft_strlen(var) + start + 1);
	i = -1;
	while (++i < start)
		ncmd[i] = cmd[i];
	j = -1;
	while (++j < ft_strlen(var))
		ncmd[i++] = var[j];
	ncmd[i] = '\0';
	cmds[index] = ncmd;
	free(cmd);
}

void	export_var(t_env *env, char **cmds)
{
	size_t		i;
	size_t		j;
	size_t		k;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		while (cmds[i][++j])
		{
			if (cmds[i][++j] == '$')
			{
				k = j;
				while (cmds[i][++k] != ' ' && cmds[i][++k])
					;
				replace_var(cmds, i, get_var_env(env, get_kw(cmds[i], j, k)), j);
			}
		}
	}
}
