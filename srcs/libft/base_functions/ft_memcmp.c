/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:04:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/19 11:36:53 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	if (s1 && s2)
	{
		i = 0;
		c1 = (unsigned char *) s1;
		c2 = (unsigned char *) s2;
		while (i < n)
		{
			if (c1[i] != c2[i])
				return (c1[i] - c2[i]);
			i++;
		}
	}
	return (0);
}
