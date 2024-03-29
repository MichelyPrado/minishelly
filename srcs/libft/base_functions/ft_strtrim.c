/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:19:39 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/19 11:42:04 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strrchr(set, s1[start]) != NULL)
		start++;
	len = ft_strlen (s1 + start);
	if (len != 0)
	{
		while (s1[start + len - 1]
			&& ft_strrchr(set, s1[start + len - 1]) != NULL)
			len -= 1;
	}
	return (ft_substr(s1, start, len));
}
