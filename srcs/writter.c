/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 11:04:49 by andrew            #+#    #+#             */
/*   Updated: 2022/01/07 22:14:20 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	putstr(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
		write(fd, &s[i++], 1);
}

void	putstr_endl(int fd, char *s)
{
	putstr(fd, s);
	write(fd, "\n", 1);
}

void	put_error(char *er, char *cmd)
{
	int	i;
	int	j;

	if (cmd == NULL)
		printf("%s\n", er);
	else
	{
		i = 0;
		while (cmd[i] != ' ' && cmd[i])
				i++;
		j = -1;
		while (++j < i)
			printf("%c", cmd[j]);
		printf("%s\n", er);
	}
}
