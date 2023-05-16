/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 12:06:36 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/16 01:27:54 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token *swap_tokens(t_token *bk, t_token **md, t_token *end)
{
	t_token	*tmp;

	tmp = *md;
	if (bk)
		bk->next = end;
	tmp->next = end->next;
	end->next = tmp;
   return (end);
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

char    **rm_first_item(char **array)
{
	int		i;
	char	**tmp;

	i = 0;
	while (array[i])
		i++;
    if (i <= 1)
        return (NULL);
    tmp = ft_calloc(sizeof(char *), i);
	i = 1;
	while (array[i])
	{
		tmp[i - 1] = array[i];
		i++;
	}
	if (array)
		free(array);
	return (tmp);
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
