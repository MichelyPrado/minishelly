/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 21:40:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/19 11:36:36 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
