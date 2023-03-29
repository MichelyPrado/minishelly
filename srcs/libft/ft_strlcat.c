/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 18:14:56 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 18:15:26 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	d;
	size_t	s;
	size_t	i;

	d = ft_strlen(dst);
	s = ft_strlen(src);
	i = 0;
	if (size <= d)
		return (s + size);
	else
	{
		while (src[i] && (size - 1) > (d + i))
		{
			dst[d + i] = src[i];
			i++;
		}
		dst[d + i] = '\0';
		return (d + s);
	}
}
