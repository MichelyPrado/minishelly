/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:04:31 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:49:00 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	hash_func(char *cmd, t_keyword_map *keymap)
{
	int	i;

	if (!cmd || ft_isspace(cmd))
		return (OP_DEFAULT);
	i = 0;
	while (i < 14)
	{
		if (ft_strcmp(cmd, keymap[i].keyword) == 0)
			return (keymap[i].type);
		i++;
	}
	return (OP_CMD);
}
