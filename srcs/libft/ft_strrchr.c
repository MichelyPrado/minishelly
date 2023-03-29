/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 20:56:40 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 20:09:46 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (c >= 127)
		c = c % 256;
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	else
	{
		while (s[i])
			i++;
		while (i >= 0)
		{
			if (s[i] == c)
				return ((char *)s + i);
			i--;
		}
	}
	return (NULL);
}
