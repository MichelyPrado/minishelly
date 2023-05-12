/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:06:05 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/12 12:11:23 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_token_new(char **cmds, int type)
{
	t_token	*node;

	node = malloc(sizeof(t_token));
	if (!node)
		return (NULL);
	node->token = cmds;
	node->type = type;
	node->next = NULL;
	return (node);
}

t_token	*ft_token_last(t_token *node)
{
	t_token	*last;

	last = node;
	if (!last)
		return (NULL);
	while (last->next != NULL)
		last = last->next;
	return (last);
}

void	ft_token_add_end(t_token **node, t_token *new)
{
	t_token	*tail;

	if (!node || !new)
		return ;
	tail = ft_token_last(*node);
	if (tail == NULL)
		*node = new;
	else
		tail->next = new;
}

void	ft_token_free(t_token **node)
{
	t_token	*head;
	t_token	*temp;

	head = *node;
	temp = *node;
	while (temp)
	{
		temp = head->next;
		if (head->token)
			clean_strlist(&head->token);
		free(head);
		head = temp;
	}
	*node = NULL;
}
