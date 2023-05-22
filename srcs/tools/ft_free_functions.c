/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 00:36:44 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 15:15:31 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



void	clean_strlist(char ***strs)
{
	int	i;

	i = 0;
	if (!(*strs))
		return ;
	if (*strs)
	{
		while ((*strs)[i])
		{
			free((*strs)[i]);
			(*strs)[i] = NULL;
			i++;
		}
		free(*strs);
	}
	*strs = NULL;
}

void	clean_lstitens(char **lst)
{
	int	i;

	i = 0;
	if (lst)
	{
		while (lst[i])
		{
			free(lst[i]);
			lst[i] = NULL;
			i++;
		}
	}
}

void	free_node_only(t_token **node)
{
	t_token	*head;
	t_token	*temp;

	head = *node;
	temp = *node;
	while (temp)
	{
		temp = head->next;
		if (head)
		{
			free(head);
			head = NULL;
		}
		head = temp;
	}
	*node = NULL;
}

void	ft_node_free(t_token **node)
{
	if (*node)
	{
		if ((*node)->token)
			clean_strlist(&(*node)->token);
		free((*node));
		*node = NULL;
	}
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
		ft_node_free(&head);
		head = temp;
	}
	*node = NULL;
}