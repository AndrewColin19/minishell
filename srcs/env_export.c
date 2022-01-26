/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:13:12 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 12:22:32 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**dup_tab(char **tab)
{
	int		i;
	char	**tab_dup;

	i = 0;
	while (tab[i])
		i++;
	tab_dup = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (tab[i])
	{
		tab_dup[i] = ft_strdup(tab[i]);
		i++;
	}
	tab_dup[i] = NULL;
	return (tab_dup);
}

void	aff_var_export_tab(int fd, char **tab)
{
    int i;
    int j;
    int k;
    
    i = -1;
    while (tab[++i])
    {
        k = 0;
        putstr(fd, "declare -x ");
        j = 0;
        while (tab[i][j])
        {
            write(1, &tab[i][j], 1);
            if (tab[i][j] == '=' && k == 0)
            {
                write(1, "\"", 1);
                k = 1;
            }
            if (tab[i][j + 1] == '\0' && k == 1)
                write(1, "\"", 1);
            j++;
        }
        write(1, "\n", 1);
    }
}

void	order_by_asc(char **tab)
{
	char	*temp;
	int		i;
	int		j;

	i = -1;
	while (tab[++i])
	{
		j = -1;
		while (tab[++j])
		{
			if (ft_strncmp(tab[i], tab[j], ft_strlen(tab[i])) < 0)
			{
				temp = tab[i];
				tab[i] = tab[j];
				tab[j] = temp;
			}
		}
	}
}

void	aff_export(int fd, t_env *g_env)
{
	char	**tab;

	tab = dup_tab(g_env->var_env);
	order_by_asc(tab);
	aff_var_export_tab(fd, tab);
//free_cmds(tab);
}
