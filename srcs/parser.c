/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:11:18 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/13 18:41:52 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_letter(char *s, int i, int j, char c)
{
	s[i + j] = c;
	return (1);
}

char	*symbol_delimiter(char *src)
{
	int		i;
	int		c_pipe;
	char	*dst;
	int		delimiters;

	i = 0;
	c_pipe = 0;
	if (src == NULL)
		return (NULL);
	delimiters = count_delimiter(src);
	dst = ft_calloc(sizeof(char), delimiters + 1);
	while (src[i])
	{
		i += add_delimiters('|', &c_pipe, &dst[i], &src[i]);
		i += add_delimiters('<', &c_pipe, &dst[i], &src[i]);
		i += add_delimiters('>', &c_pipe, &dst[i], &src[i]);
		dst[i + c_pipe] = src[i];
		i++;
	}
	return (dst);
}

int	count_delimiter(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			j += 2;
		}
		i++;
	}
	return (i + j);
}

int	add_delimiters(char symbol, int *c_pipe, char *s, char *str)
{
	int	i;

	i = 0;
	if (str[i] == symbol)
	{
		*c_pipe += add_letter(s, i, *c_pipe, NO_PRINT);
		*c_pipe += add_letter(s, i, *c_pipe, str[i]);
		i += add_letter(s, i, *c_pipe, NO_PRINT);
	}
	return (i);
}
