/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 09:47:02 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 18:33:51 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	insert_char_in_string(char *dst, int j, char c)
{
	dst[j] = c;
	return (1);
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

int	check_quotes(char *src, char quote, int jump)
{
	char	*p;

	p = NULL;
	if (*src == quote)
	{
		p = ft_strchr(src + 1, quote);
		if (p)
		{
			jump += (p - src) + 1;
			if (src[(p - src) + 1] == DQUOTE)
				return (check_quotes(&src[p - src] + 1, DQUOTE, jump));
			if (src[(p - src) + 1] == SQUOTE)
				return (check_quotes(&src[p - src] + 1, SQUOTE, jump));
			return (jump);
		}
		else
			return (-1);
	}
	return (0);
}
