/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andrew <andrew@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:25:03 by andrew            #+#    #+#             */
/*   Updated: 2021/12/11 15:56:13 by andrew           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cmd_echo(char **cmd)
{
	int	ln;
	int	i;

	ln = 1;
	i = 1;
	if (ft_strncmp(cmd[i], "-n", ft_strlen(cmd[i])) == 0)
	{
		ln = 0;
		i++;
	}
	while (cmd[i])
		putstr(0, cmd[i++]);
	if (ln)
		write(0, "\n", 1);
}

void	cmd_pwd(char *path)
{
	if (path != NULL)
		printf("%s\n", path);
}