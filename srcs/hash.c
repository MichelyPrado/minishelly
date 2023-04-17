/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 17:04:31 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/16 20:00:53 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		hash_func(char *cmd, t_keyword_map *keymap)
{
	int	i;

	if (!cmd || ft_isspace(cmd))
		return (OP_DEFAULT);
	i = 0;
	while (i < 14)
	{
		if (strcmp(cmd, keymap[i].keyword) == 0)
			return keymap[i].type;
		i++;
	}
	return (OP_CMD);
}

/*
t_event *hash_tbcreate() 
{
	int		i;
	t_event	*table;

	table = malloc(sizeof(t_event *) * 160);
	table[0] = (t_event){.key = 0, .value = OP_DEFAULT};
	table[1] = (t_event) {.key = 0, .value = OP_AND};
	table[2] = (t_event) {.key = 0, .value = OP_OR};
	table[3] = (t_event) {.key = 0, .value = OP_PIPE};
	table[4] = (t_event) {.key = 0, .value = OP_OUTPUT};
	table[5] = (t_event) {.key = 0, .value = OP_INPUT};
	table[6] = (t_event) {.key = 0, .value = OP_UNTIL};
	table[7] = (t_event) {.key = 0, .value = OP_APPEND};
	table[8] = (t_event) {.key = 0, .value = OP_CMD};
	table[9] = (t_event) {.key = 0, .value = OP_EXIT};
	table[10] = (t_event) {.key = 0, .value = OP_CD};
	table[11] = (t_event) {.key = 0, .value = OP_ENV};
	table[12] = (t_event) {.key = 0, .value = OP_UNSET};
	table[13] = (t_event) {.key = 0, .value = OP_EXPORT};
	table[14] = (t_event) {.key = 0, .value = OP_PWD};
	table[15] = (t_event) {.key = 0, .value = OP_ECHO};
	return (table);
}
*/