/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:57 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/19 13:48:58 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// receber uma string separada por *
// while que percore a string contando os caracteres e
// quando achar um * ft_substr(new_parser, pos_inicial, qtd de caracteres)
// criar um node e armazenar o comando dentro
// passa para o proximo node
// repete até a string acabar

int	change_quotes(char *src, char quote, int *i)
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
			src[0] = NO_PRINT;
			src[p - src] = NO_PRINT;
			*i += jump;
			if (src[(p - src) + 1] == DQUOTE)
				change_quotes(&src[p - src] + 1, DQUOTE, i);
			if (src[(p - src) + 1] == SQUOTE)
				change_quotes(&src[p - src] + 1, SQUOTE, i);
			return (jump);
		}
		else
			return (-1);
	}
	return (0);
}

char	*ft_token_repair(char *token)
{
	int	i;

	i = 0;
	while (token[i] != '\0')
	{
		change_quotes(&token[i], DQUOTE, &i);
		change_quotes(&token[i], SQUOTE, &i);
		if (token[i] == 32)
			token[i] = NO_PRINT;
		if (token[i] != '\0')
			i++;
	}
	return (token);
}

t_token	*ft_create_tokens(t_sys_config *mini)
{
	int		i;
	t_types	op;
	t_token	*tokens;
	char	**token;
	char	**pieces;

	i = 0;
	pieces = ft_split(mini->new_parser, NO_PRINT);
	tokens = (t_token *){0};
	while (pieces[i])
	{
		pieces[i] = ft_token_repair(pieces[i]);
		token = ft_split(pieces[i], NO_PRINT);
		op = tag_token(token[0]);
		if (op)
			ft_token_add_end(&tokens, ft_token_new(token, op));
		else
			free_cmds(token);
		i++;
	}
	free_cmds(pieces);
	return (tokens);
}

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '\t' || str[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}

t_types	tag_token(char *cmd)
{
	t_keyword_map	*keymap;

	keymap = (t_keyword_map[]){
	{"&&", OP_AND},
	{"|", OP_PIPE},
	{"||", OP_OR},
	{">", OP_OUTPUT},
	{"<", OP_INPUT},
	{"<<", OP_UNTIL},
	{">>", OP_APPEND},
	{"exit", OP_EXIT},
	{"cd", OP_CD},
	{"env", OP_ENV},
	{"unset", OP_UNSET},
	{"export", OP_EXPORT},
	{"pwd", OP_PWD},
	{"echo", OP_ECHO}
	};
	return (hash_func(cmd, keymap));
}
