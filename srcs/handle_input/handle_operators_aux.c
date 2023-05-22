/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operators_aux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 23:14:37 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 15:10:02 by msilva-p         ###   ########.fr       */
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

t_token	*set_pipe(t_token **head, t_token *bk, t_token *end)
{
	t_token	*tmp;
	t_token	*cpy;

	if (bk->type == OP_PIPE)
		return (*head);
	cpy = ft_token_new(ft_split("|", ' '), OP_PIPE);
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
	(void)end;
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
