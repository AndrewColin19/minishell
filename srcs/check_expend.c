/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_expend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:32:48 by acolin            #+#    #+#             */
/*   Updated: 2022/01/05 13:56:08 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_expend_cmds(char *cmds)
{
	int	i;

	i = 0;
	while (cmds[i] == ' ')
		i++;
	if (cmds[i] == '"' && cmds[ft_strlen(cmds) - 1])
		printf("expend\n");
	return (1);
}