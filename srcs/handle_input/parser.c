/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:11:18 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 23:11:34 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	add_delimiters(char symbol, int *j, char *dst, char *c)
{
	if (*c == symbol && check_next_eq(symbol, c) && *c != '|')
	{
		*j += insert_char_in_string(dst, *j, NO_PRINT);
		*j += insert_char_in_string(dst, *j, *c);
		*j += insert_char_in_string(dst, *j, *c);
		*j += insert_char_in_string(dst, *j, NO_PRINT);
		return (2);
	}
	else if (*c == symbol)
	{
		*j += insert_char_in_string(dst, *j, NO_PRINT);
		*j += insert_char_in_string(dst, *j, *c);
		*j += insert_char_in_string(dst, *j, NO_PRINT);
		return (1);
	}
	return (0);
}

t_err	check_readline_aux(char *src, t_sys_config *ms)
{
	if (src == NULL)
		return (ERR_NOLINE);
	ms->nlen_parser = count_delimiter(src, 0);
	if (ms->nlen_parser == -1)
		return (ERR_QUOTES);
	ms->new_parser = ft_calloc(sizeof(char), ms->nlen_parser + 1);
	return (0);
}

t_err	check_readline(char *src, t_sys_config *mini)
{
	int		i;
	int		j;
	int		jump;

	i = 0;
	j = 0;
	jump = check_readline_aux(src, mini);
	if (jump)
		return (jump);
	while (src[i])
	{
		jump = 0;
		jump += jump_quotes(&src[i], mini, DQUOTE, &j);
		jump += jump_quotes(&src[i], mini, SQUOTE, &j);
		jump += add_delimiters('|', &j, mini->new_parser, &src[i]);
		jump += add_delimiters('<', &j, mini->new_parser, &src[i]);
		jump += add_delimiters('>', &j, mini->new_parser, &src[i]);
		if (!src[jump])
			break ;
		if (!jump)
			mini->new_parser[j++] = src[i++];
		i += jump;
	}
	return (NO_ERR);
}

int	jump_quotes_aux(char *readline, int i)
{
	int	j;
	int	jump;

	j = 0;
	jump = 0;
	jump = check_quotes(&readline[i], DQUOTE, jump);
	if (jump == -1)
		return (-1);
	j += jump;
	jump = check_quotes(&readline[i], SQUOTE, jump);
	if (jump == -1)
		return (-1);
	j += jump;
	return (j);
}

int	count_delimiter(char *readline, int j)
{
	int		i;

	i = -1;
	if (readline == NULL)
		return (0);
	while (readline[++i])
	{
		if (jump_quotes_aux(readline, i) == -1)
			return (-1);
		i += jump_quotes_aux(readline, i);
		if (readline[i] == '|' || readline[i] == '<' || readline[i] == '>')
		{
			if (readline[i] == '|')
				*get_num_pipes() += 1;
			else if (check_next_eq(readline[i], &readline[i]))
				i++;
			j += 2;
		}
		if (!readline[i])
		{
			i++;
			break ;
		}
	}
	return (i + j);
}
