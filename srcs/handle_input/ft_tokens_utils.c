/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:06:36 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/18 16:35:08 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*get_back_token(t_token *head, t_token *current)
{
	while (head)
	{
		if (head->next == current)
			break ;
		head = head->next;
	}
	return (head);
}

void	ft_swap_token(t_token **head, t_token **current, t_token **dest)
{
	t_token	*tmp;
	t_token	*htmp;
	t_token	*aux = NULL;

	tmp = NULL;
	htmp = NULL;
	aux = NULL;
	if (!*dest)
		return ;
	if (*current == *head)
		*head = *dest;
	else
		htmp = *head;
	tmp = (*dest)->next;
	(*dest)->next = *current;
	aux = (*current)->next;
    (*current)->next = tmp;
	if (htmp)
		get_back_token(htmp, *current)->next = aux;
}

t_token	*copy_token(t_token *bk, t_token **md, t_token *end)
{
	t_token	*cpy;

	cpy = ft_token_new(end->token, end->type);
	if (bk)
		bk->next = cpy;
	cpy->next = *md;
	return (cpy);
}



void	correct_puts(t_token *md, t_token *end)
{
	char	**tmp;

	tmp = NULL;
	if (md->type >= 4 && md->type <= 7)
	{
		tmp = ft_calloc(sizeof(char *), 3);
		tmp[0] = md->token[0];
		tmp[1] = end->token[0];
		if (md->token)
			free(md->token);
		md->token = tmp;
		end->token = rm_first_item(end->token);
		if (!end->token)
		{
			md->next = end->next;
			ft_node_free(&end);
		}
	}
}
