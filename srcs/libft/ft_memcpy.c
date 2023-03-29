/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:05:32 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 16:25:12 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*u_dest;
	unsigned char	*u_src;
	size_t			i;

	i = 0;
	u_dest = (unsigned char *)dest;
	u_src = (unsigned char *)src;
	while (i < n)
	{
		u_dest[i] = u_src[i];
		i++;
	}
	return (dest);
}
