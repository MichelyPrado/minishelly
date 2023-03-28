/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:40:09 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 10:50:31 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*vet;
	int		new;

	new = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (NULL);
	if (new / size != nmemb)
		return (NULL);
	vet = malloc (nmemb * size);
	if (!vet)
		return (NULL);
	ft_bzero(vet, nmemb * size);
	return (vet);
}
