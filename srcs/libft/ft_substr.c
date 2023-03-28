/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:13:32 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 20:33:13 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	lenmax;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s) - start)
		lenmax = ft_strlen(s) - start;
	else
		lenmax = len;
	if (!s)
		return (NULL);
	subs = (char *)malloc(sizeof(char) * (lenmax + 1));
	if (!subs)
		return (NULL);
	ft_strlcpy(subs, s + start, lenmax + 1);
	return (subs);
}
