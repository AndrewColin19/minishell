/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2022/01/04 16:49:41 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(int fd, char *cmd)
{
    int i;
    int ln;

    i = ft_strlen(ECHO) + 1;
    ln = 1;
    if (cmd[i] == '-' && is_only_n(cmd + i + 1))
        ln = 0;
    if (ln)
        putstr_endl(fd, cmd + i);
    else
    {
        while (cmd[i] && cmd[i] != ' ')
            i++;
        putstr(fd, cmd + i);
    }   
}

void	cmd_pwd(int fd, t_env *env)
{
	char	*path;

	path = get_var_env(env, "PWD");
	if (path != NULL)
		putstr_endl(fd, path);
}

void	cmd_env(int fd, t_env g_env)
{
	int	i;

	i = -1;
	while (g_env.var_env[++i])
		putstr_endl(fd, g_env.var_env[i]);
}

void	cmd_cd(t_env *g_env, char *cmd)
{
	int		i;
	char	*path;
	
	i = 0;
	while (cmd[i] && cmd[i] != ' ')
		i++;
	if (cmd[i] == '\0')
		path = get_var_env(g_env, "HOME");
	else
		path = cmd + (++i);
	if (chdir(path) == -1)
		printf("cd: %s: Aucun fichier ou dossier de ce type\n", path);
	else 
	{
		add_var_env(g_env, "OLDPWD", get_var_env(g_env,"PWD"));
		set_var_env(g_env, "PWD", path);
	}
}
