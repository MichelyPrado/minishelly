/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:37:42 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 18:36:23 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	if (ft_strlen(little) == 0)
		return ((char *)big);
	else
	{
		while (big[i] && i < len)
		{
			j = 0;
			while (little[j] == big[j + i] && (i + j) < len)
			{
				if (!little[j + 1])
				{
					str = (char *)big + i;
					return (str);
				}
				j++;
			}
			i++;
		}
	}
	return (NULL);
}
