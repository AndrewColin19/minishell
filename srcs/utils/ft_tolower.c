/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:48:56 by acolin            #+#    #+#             */
/*   Updated: 2022/01/27 14:22:09 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * convertit la lettre c en minuscule si c'est possible.
 *
 * \param	c	caractère à convertir
 * \return		La valeur renvoyée est celle de la lettre convertie, 
 * 				ou bien c si la conversion n'était pas possible. 
 */
char	*ft_tolower(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[++i] >= 'A' && str[++i] <= 'Z')
			str[++i] += 32;
	}
	return (str);
}
