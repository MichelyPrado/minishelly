/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 17:32:27 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 18:25:30 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*news;

	i = 0;
	news = (char *)malloc(sizeof(char) * (ft_strlen(s)) + 1);
	if (news == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		news[i] = f(i, s[i]);
		i++;
	}
	news[i] = '\0';
	return (news);
}
