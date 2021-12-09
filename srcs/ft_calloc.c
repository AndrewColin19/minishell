/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acolin <acolin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:27:34 by acolin            #+#    #+#             */
/*   Updated: 2021/12/09 13:25:40 by acolin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * remplit les n premiers octets de la zone mémoire pointée par s avec 
 * l'octet c.
 *
 * \param	*s	pointeur sur la zone mémoire
 * \param	c	octet de remplissage
 * \param	n	nombres d'octets
 * \return		renvoie un pointeur sur la zone mémoire s.
 */
static void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*a;

	a = (unsigned char *) s;
	while (n)
	{
		*a = (unsigned char) c;
		a++;
		n--;
	}
	return (s);
}

/**
 * alloue la mémoire nécessaire pour un tableau de nmemb éléments de 
 * taille size octets, et renvoie un pointeur vers la mémoire allouée. 
 * Cette zone est remplie avec des zéros. Si nmemb ou size vaut 0, calloc() 
 * renvoie soit NULL, soit un pointeur unique qui pourra 
 * être passé ultérieurement à free() avec succès.
 *
 * \param	nmemb	nombres d'élèments
 * \param	size	taille d'un élèment
 * \return			renvoient un pointeur sur la mémoire allouée, 
 * 					qui est correctement alignée pour n'importe quel type de variable. 
 *				 	Si elles échouent, elles renvoient NULL. 
 *					NULL peut également être renvoyé par un appel réussi à malloc() 
 * 					avec un argument size égal à zéro,
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*tab;

	tab = malloc(nmemb * size);
	if (!tab)
		return (NULL);
	ft_memset(tab, 0, nmemb * size);
	return ((void *)tab);
}
