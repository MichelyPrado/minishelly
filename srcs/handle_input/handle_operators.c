/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:06:35 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/21 15:01:05 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*handle_pipes(t_token **head, t_token *t)
{
	t_token	*back;

	back = *head;
	while (t)
	{
		if (!t->next)
			break ;
		while (t && (t->type >= OP_OUTPUT && t->type <= OP_APPEND))
			t = t->next;
		if (t->next && t->next->type == OP_PIPE)
			set_pipe(head, back, t->next);
		back = t;
		t = t->next;
	}
	return (*head);
}

t_token	*ft_handle_files(t_token *head, t_token *t, t_token *aux)
{
	t_token	*back;
	t_token	*tmp;

	tmp = NULL;
	back = NULL;
	while (t)
	{
		if ((t->type >= OP_OUTPUT && t->type <= OP_APPEND) && aux)
		{
			set_file_descriptor(t, aux);
			realloc_strings(back, aux);
			if (!aux->token[0])
			{
				tmp = aux->next;
				ft_node_free(&aux);
				t->next = tmp;
			}
			ft_handle_operators(&head, back);
		}
		back = t;
		t = t->next;
		if (t)
			aux = t->next;
	}
	return (head);
}

void	prepare_commands(t_sys_config *ms)
{
	t_token	*head;
	t_token	*aux;

	if (!ms->tokens)
		return ;
	head = ms->tokens;
	aux = ms->tokens->next;
	head = ft_handle_files(head, head, aux);
	head = handle_pipes(&head, head);
	ms->tokens = head;
}
