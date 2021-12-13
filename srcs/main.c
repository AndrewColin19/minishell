/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 11:01:16 by acolin            #+#    #+#             */
/*   Updated: 2021/12/11 15:54:46 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char path[PATH_BUF];

void	exec(char **cmds)
{
	int		i;
	char	**cmd;

	i = -1;
	while (cmds[++i])
	{
		cmd = ft_split(cmds[i], ' ');
		if (ft_strncmp(cmd[0], ECHO, ft_strlen(cmd[0])) == 0)
			cmd_echo(cmd);
		else if (ft_strncmp(cmd[0], PWD, ft_strlen(cmd[0])) == 0)
			cmd_pwd(path);
	}
}

int	main(void)
{
	char **cmds;

	getcwd(path, PATH_BUF);
	printf("path : %s\n", path);
	while (1)
	{
		cmds = parse(readline(SHELL_TEXT));
		
		if (cmds == NULL)
		{
			printf("Error\n");
			free_cmds(cmds);
		}
		else
			exec(cmds);
	}
}
