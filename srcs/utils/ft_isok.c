/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isok.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 17:58:31 by acolin            #+#    #+#             */
/*   Updated: 2022/01/26 18:06:52 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_isok(char *str)
{
	int l;
	int	i;

	l = 0;
	i = 0;
	while (str[i])
	{
		if(ft_isalpha(str[i]))
		{
			l = 1;
			i++;
		}
		else if (ft_isdigit(str[i]) && l == 1)
			i++;
		else
			return (0);
	}
	return (1);
}