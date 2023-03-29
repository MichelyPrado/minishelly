/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:04:09 by msilva-p          #+#    #+#             */
/*   Updated: 2022/12/12 00:55:43 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
