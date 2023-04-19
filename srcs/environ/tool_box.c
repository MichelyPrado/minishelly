/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 11:18:27 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:49:22 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Responsavel por dar join na key com o value
da variavel passada */
char	*join_key_value(char *key, char *value)
{
	char	*dst;
	int		len;

	len = (ft_strlen(key) + ft_strlen(value) + 1);
	dst = ft_calloc(sizeof(char), len);
	ft_strlcat(dst, key, len);
	if (value)
		ft_strlcat(dst, value, len);
	else
		ft_strlcat(dst, "", len);
	return (dst);
}
