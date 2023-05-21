/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 16:06:35 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/20 21:06:27 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**rm_first_item(char **array)
{
	int		i;
	char	**tmp;

	i = 0;
	while (array[i])
		i++;
	if (i < 1)
		return (NULL);
	tmp = ft_calloc(sizeof(char *), i);
	i = 1;
	while (array[i])
	{
		tmp[i - 1] = array[i];
		i++;
	}
	return (tmp);
}

void	set_file_descriptor(t_token *t, t_token *aux)
{
	char	**tmp;

	tmp = NULL;
	tmp = ft_calloc(sizeof(char *), 3);
	tmp[0] = t->token[0];
	if (aux->token)
	{
		if (*aux->token)
			tmp[1] = *aux->token;
		if (t->token)
			free(t->token);
		t->token = tmp;
		tmp = rm_first_item(aux->token);
		if (!tmp)
			return ;
		free(aux->token);
		aux->token = tmp;
	}
}

int	ft_handle_operators(t_token **head, t_token *t)
{
	if (t && (t->type >= OP_CMD && t->type <= OP_ECHO) && t->next
	&& (t->next->type >= OP_OUTPUT && t->next->type <= OP_APPEND))
	{
		ft_swap_token(head, &t, &t->next);
		return (1);
	}
	return (0);
}

t_token	*cpy(t_token **head, t_token *bk, t_token *end)
{
	t_token	*tmp;
	t_token	*cpy;

	if (bk->type == OP_PIPE)
		return (*head);
	cpy = ft_token_new(end->token, end->type);
	if (*head == bk)
	{
		cpy->next = *head;
		*head = cpy;
		return (cpy);
	}
	tmp = bk->next;
	bk->next = cpy;
	cpy->next = tmp;
	return (*head);
}


t_token	*test(t_token **head, t_token *t)
{
	t_token *back;

	back = *head;
	while (t)
	{
		while (t && (t->type >= OP_OUTPUT && t->type <= OP_APPEND))
			t = t->next;
		if (t->next && t->next->type == OP_PIPE)
			cpy(head, back, t->next);
		back = t;
		t = t->next;
	}
	return (*head);
}

t_token	*ft_handle_files(t_token *t)
{
	t_token	*aux;
	t_token	*back;
	t_token	*tmp;
	t_token	*head;

	tmp = NULL;
	back = NULL;
	head = t;
	aux = t->next;
	if (!aux)
		return (t);
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
	head = test(&head, head);
	return (head);
}



int	realloc_strings(t_token *back, t_token *end)
{
	char	**tmp;

	tmp = NULL;
	if (end->token)
	{
		if (back && back->type >= OP_CMD && back->type <= OP_ECHO)
		{
			tmp = ft_listjoin(back->token, end->token);
			free(end->token);
			end->token = ft_calloc(sizeof(char *), 0 + 1);
			back->token = tmp;
			return (1);
		}
	}
	return (0);
}
