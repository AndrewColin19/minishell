/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2021/12/15 15:34:27 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env env;

void	exec(char **cmds, t_env *env)
{
	int		i;

	i = -1;
	while (cmds[++i])
	{
		if (ft_strncmp(cmds[i], ECHO, ft_strlen(ECHO)) == 0)
			cmd_echo(cmds[i]);
		else if (ft_strncmp(cmds[i], PWD, ft_strlen(PWD)) == 0)
			cmd_pwd(env->path);
	}
}

void	init(t_env *env)
{
	char *pwd;

	getcwd(env->path, PATH_BUF);
	env->variable = malloc(sizeof(char *) * 1);
	pwd = ft_strjoin("PWD=", env->path);
	env->variable[0] = malloc(sizeof(char) * ft_strlen(pwd));
	env->variable[0] = pwd;
	printf("%s\n", env->variable[0]);
}

int	main(void)
{
	char **cmds;

	init(&env);
	while (1)
	{
		cmds = parse(readline(SHELL_TEXT));
		if (cmds == NULL)
		{
			printf("Error\n");
			free_cmds(cmds);
		}
		else
			exec(cmds, &env);
	}
}
