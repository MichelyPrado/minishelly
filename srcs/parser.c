/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:11:18 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/28 11:26:48 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_delimiters(char symbol, int *j, char *dst, char *actual_char)
{
	if (*actual_char == symbol && check_next(symbol, actual_char))
	{
		*j += add_character(dst, *j, NO_PRINT);
		*j += add_character(dst, *j, *actual_char);
		*j += add_character(dst, *j, *actual_char);
		*j += add_character(dst, *j, NO_PRINT);
		return (2);
	}
	else if (*actual_char == symbol && *actual_char != '&')
	{
		*j += add_character(dst, *j, NO_PRINT);
		*j += add_character(dst, *j, *actual_char);
		*j += add_character(dst, *j, NO_PRINT);
		return (1);
	}
	return (0);
}

void	symbol_delimiter(char *src, t_sys_config *mini)
{
	int		jump;
	int		i;
	int		j;

	i = 0;
	j = 0;
	jump = 0;
	if (src == NULL)
		return ;
	mini->nlen_parser = count_delimiter(src);
	mini->new_parser = ft_calloc(sizeof(char), mini->nlen_parser + 1);
	while (src[i])
	{
		j += jump_quotes(&src[i], mini, DQUOTE, &i);
		j += jump_quotes(&src[i], mini, SQUOTE, &i);
		i += add_delimiters('|', &j, mini->new_parser, &src[i]);
		i += add_delimiters('<', &j, mini->new_parser, &src[i]);
		i += add_delimiters('>', &j, mini->new_parser, &src[i]);
		i += add_delimiters('&', &j, mini->new_parser, &src[i]);
		mini->new_parser[j++] = src[i++];
	}
}

int	count_delimiter(char *readline)
{
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (readline == NULL)
		return (0);
	while (readline[++i])
	{
		check_quotes(&readline[i], DQUOTE, &i);
		check_quotes(&readline[i], SQUOTE, &i);
		if (readline[i] == '|' || readline[i] == '<' \
		|| readline[i] == '>' || readline[i] == '&')
		{
			if (readline[i] == '&' && !check_next('&', &readline[i]))
				continue ;
			else if (check_next(readline[i], &readline[i]))
				i++;
			j += 2;
		}
	}
	return (i + j);
}
