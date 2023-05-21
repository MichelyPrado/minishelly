/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:57 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/21 14:04:06 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	change_quotes(char *src, char quote, int *i, int schar)
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
			src[0] = schar;
			src[p - src] = schar;
			*i += jump;
			if (check_next_eq(DQUOTE, &src[(p - src)]))
				change_quotes(&src[p - src] + 1, DQUOTE, i, schar);
			if (check_next_eq(SQUOTE, &src[(p - src)]))
				change_quotes(&src[p - src] + 1, SQUOTE, i, schar);
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
		change_quotes(&token[i], DQUOTE, &i, -42);
		change_quotes(&token[i], SQUOTE, &i, -21);
		if (token[i] == 32)
			token[i] = NO_PRINT;
		if (token[i] != '\0')
			i++;
	}
	return (token);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	int		size;
	char	*new;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] != -42 && str[i] != -21)
			size++;
		i++;
	}
	new = ft_calloc(sizeof(char), size + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != -42 && str[i] != -21)
			new[j++] = str[i];
		i++;
	}
	return (new);
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
	tokens = NULL;
	while (pieces[i])
	{
		pieces[i] = ft_token_repair(pieces[i]);
		search_for_symbol(&pieces[i], '$', mini->env);
		if (!ft_strlen(pieces[i]))
			return (NULL);
		pieces[i] = remove_quotes(pieces[i]);
		token = ft_split(pieces[i], NO_PRINT);
		op = tag_token(token[0]);
		if (op)
			ft_token_add_end(&tokens, ft_token_new(token, op));
		else
		{
			clean_strlist(token);
			token = NULL;
		} 
		i++;
	}
	clean_strlist(pieces);
	pieces = NULL;
	return (tokens);
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

int	hash_func(char *cmd, t_keyword_map *keymap)
{
	int	i;

	if (!cmd || ft_is_allspace(cmd))
		return (OP_DEFAULT);
	i = 0;
	while (i < 14)
	{
		if (ft_strcmp(cmd, keymap[i].keyword) == 0)
			return (keymap[i].type);
		i++;
	}
	return (OP_CMD);
}
