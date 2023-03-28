/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:47:02 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/28 09:50:23 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_character(char *dst, int j, char c)
{
	dst[j] = c;
	return (1);
}

int	check_next(char symbol, char *str)
{
	if (*(str + 1) == symbol)
		return (1);
	return (0);
}

int	jump_quotes(char *src, t_sys_config *mini, char quote, int *i)
{
	int		jump;
	char	*p;
	char	*aux;

	p = NULL;
	aux = NULL;
	if (*src == quote)
	{
		p = ft_strchr(src + 1, quote);
		if (p)
		{
			jump = (p - src) + 1;
			aux = ft_substr(src, 0, jump);
			ft_strlcat(mini->new_parser, aux, mini->nlen_parser);
			*i += jump;
			if (aux)
				free (aux);
			return (jump);
		}
	}
	return (0);
}

int	check_quotes(char *src, char quote, int *i)
{
	int		jump;
	char	*p;

	p = NULL;
	if (*src == quote)
	{
		p = ft_strchr(src + 1, quote);
		if (p)
		{
			jump = (p - src) + 1;
			*i += jump;
			return (jump);
		}
	}
	return (0);
}
