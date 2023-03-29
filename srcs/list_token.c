/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:06:05 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/29 05:21:36 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *ft_token_new(char **cmds, char *operator, int type)
{
    t_token *node;
    node = malloc(sizeof(t_token));
    node->cmds = cmds;
    node->operator = operator;
    node->type = type;
    node->next = NULL;
    return (node);
}

