/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:47:02 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/11 16:58:24 by dapaulin         ###   ########.fr       */
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

int	jump_quotes(char *src, t_sys_config *mini, char quote, int *j)
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
			*j += jump;
			if (aux)
				free (aux);
			return (jump);
		}
	}
	return (0);
}

//função que verifica se a pos atual é ' ou ", quando ela encontrar
//ela conta a quantidade de posições até encontrar a ' ou " que fecha
//retorna a quantidade de posições que ela pulou (jump)
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
			if (src[(p - src) + 1] == DQUOTE)
				check_quotes(&src[p - src] + 1, DQUOTE, i);
			if (src[(p - src) + 1] == SQUOTE)
				check_quotes(&src[p - src] + 1, SQUOTE, i);
			return (jump);
		}
		else
			return (-1);
	}
	return (0);
}
