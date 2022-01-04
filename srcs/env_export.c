/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:52:01 by acolin            #+#    #+#             */
/*   Updated: 2022/01/04 16:55:21 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_char(char *cmd, size_t start, size_t end)
{
	size_t	i;
	size_t	j;
	char	*deb;

	if (end <= start)
		return (NULL);
	deb = ft_calloc(1, end - start + 1);
	if (!deb)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
		deb[j++] = cmd[i++];
	deb[j] = '\0';
	return (deb);
}

void	insert_code(char **cmd, size_t *start)
{
	char	*debut;
	char	*fin;
	char	*tmp;
	
	debut = get_char(*cmd, 0, *start);
	fin = get_char(*cmd, *start + 2, ft_strlen(*cmd));
	if (fin)
	{
		tmp = ft_strjoin(debut, "258");
		*cmd = ft_strjoin(tmp, fin);
	}
	else
		*cmd = ft_strjoin(debut, "258");
}

void	insert(char **cmd, char *var, size_t *start, size_t end)
{
	char	*debut;
	char	*fin;
	char	*tmp;
	
	
	if (!var)
		var = "";
	debut = get_char(*cmd, 0, *start);
	fin = get_char(*cmd, end, ft_strlen(*cmd));
	if (fin)
	{
		tmp = ft_strjoin(debut, var);
		*cmd = ft_strjoin(tmp, fin);
	}
	else
		*cmd = ft_strjoin(debut, var);
	*start += ft_strlen(var) - 1;
}

void	export_var(char **cmds)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	while (cmds[++i])
	{
		j = -1;
		while (cmds[i][++j])
		{
			if (cmds[i][j] == '$' && ft_isalnum(cmds[i][j + 1]))
			{	
				if (cmds[i][j + 1] == '$')
					insert_code(&cmds[i], &j);
				else
				{
					k = j;
					while (ft_isalnum(cmds[i][++k]))
						;
					insert(&cmds[i], get_var_env(&g_env,
						get_char(cmds[i], j + 1, k)), &j, k);
				}
			}	
		}
	}
}
