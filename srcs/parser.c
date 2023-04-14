/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:11:18 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/14 15:38:40 by dapaulin         ###   ########.fr       */
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

t_err	check_readline(char *src, t_sys_config *mini)
{
	int		jump;
	int		i;
	int		j;

	i = 0;
	j = 0;
	jump = 0;
	if (src == NULL)
		return (ERR_NOLINE);
	mini->nlen_parser = count_delimiter(src);
	if (mini->nlen_parser == -1)
		return (ERR_QUOTES);
	mini->new_parser = ft_calloc(sizeof(char), mini->nlen_parser + 1);
	while (src[i])
	{
		jump = 0;
		jump += jump_quotes(&src[i], mini, DQUOTE, &j);
		jump += jump_quotes(&src[i], mini, SQUOTE, &j);
		jump += add_delimiters('|', &j, mini->new_parser, &src[i]);
		jump += add_delimiters('<', &j, mini->new_parser, &src[i]);
		jump += add_delimiters('>', &j, mini->new_parser, &src[i]);
		jump += add_delimiters('&', &j, mini->new_parser, &src[i]);
		if (!src[i + jump])
			break ;
		if (!jump)
			mini->new_parser[j++] = src[i++];
		i += jump;
}
	return (NO_ERR);
}

int	count_delimiter(char *readline)
{
	int		i;
	int		j;
	int		jump;

	i = -1;
	j = 0;
	jump = 0;
	if (readline == NULL)
		return (0);
	while (readline[++i])
	{
		jump = 0;
		jump = check_quotes(&readline[i], DQUOTE, jump);
		if (jump == -1)
			return (-1);
		i += jump;
		jump = check_quotes(&readline[i], SQUOTE, jump);
		if (jump == -1)
			return (-1);
		i += jump;
		if (readline[i] == '|' || readline[i] == '<' \
		|| readline[i] == '>' || readline[i] == '&')
		{
			if (readline[i] == '&' && !check_next('&', &readline[i]))
				continue ;
			else if (check_next(readline[i], &readline[i]))
				i++;
			j += 2;
		}
		if (!readline[i])
		{
			i++;
			break;
		}
	}
	return (i + j);
}
