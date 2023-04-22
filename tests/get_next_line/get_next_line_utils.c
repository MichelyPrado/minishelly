/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 09:31:00 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/13 23:45:36 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	g_ft_strlen(const char *str)
{
	int	size;

	size = 0;
	while (str[size])
		size++;
	return (size);
}

char	*g_ft_strchr(const char *str, int c)
{
	size_t	i;
	char	cached_c;

	i = 0;
	cached_c = (char)c;
	while (str[i] && str[i] != cached_c)
		i++;
	if (str[i] == cached_c)
		return (&((char *)str)[i]);
	return (0);
}

char	*g_ft_strdup(const char *s, size_t size)
{
	char	*ptr;

	ptr = (char *) malloc(size * sizeof(char) + 1);
	if (!ptr)
		return (NULL);
	g_ft_strlcpy(ptr, s, size + 1);
	return (ptr);
}

void	g_lstadd_back(t_buffer **lst, int creat_lst)
{
	t_buffer	*tail;
	t_buffer	*head;
	t_buffer	*new;

	new = malloc(sizeof(t_buffer));
	if (!new)
		return ;
	new -> content = NULL;
	new -> next = NULL;
	if (!creat_lst)
	{
		head = *lst;
		while (head)
		{
			tail = head;
			head = head->next;
		}
		tail -> next = new;
	}
	else
		*lst = new;
}

void	g_lstclear(t_buffer **lst, void (*del)(void *))
{
	t_buffer	*head;
	t_buffer	*next;

	head = *lst;
	next = *lst;
	while (next)
	{
		head = head -> next;
		del(next -> content);
		free(next);
		next = head;
	}
	*lst = NULL;
}
