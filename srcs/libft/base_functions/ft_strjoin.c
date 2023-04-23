/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 23:11:08 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/22 14:13:13 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*new_str;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	new_str = (char *) ft_calloc((len_s1 + len_s2) + 1,sizeof(char));
	if (!new_str)
		return (new_str);
	ft_strlcpy(new_str, s1, len_s1 + 1);
	ft_strlcpy(&new_str[len_s1], s2, len_s2 + 1);
	return (new_str);
}