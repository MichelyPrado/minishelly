/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:13:32 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/19 11:42:07 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
