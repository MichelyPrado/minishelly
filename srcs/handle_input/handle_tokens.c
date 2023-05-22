/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:57 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/22 02:24:16 by dapaulin         ###   ########.fr       */
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
				change_quotes(&src[p - src] + 1, DQUOTE, i, -42);
			if (check_next_eq(SQUOTE, &src[(p - src)]))
				change_quotes(&src[p - src] + 1, SQUOTE, i, -21);
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
	if (str)
		free(str);
	return (new);
}

t_token	*ft_create_tokens(t_sys_config *ms)
{
	int		i;
	t_types	op;
	char	**token;
	char	**pieces;

	i = 0;
	pieces = ft_split(ms->new_parser, NO_PRINT);
	while (pieces[i])
	{
		pieces[i] = ft_token_repair(pieces[i]);
		search_for_symbol(&pieces[i], '$', ms->env);
		// verificar se essa linha não vai dar erro.
		if (!ft_strlen(pieces[i]))
		{
			clean_strlist(&pieces);	
			return (NULL);
		}
		pieces[i] = remove_quotes(pieces[i]);
		token = ft_split(pieces[i], NO_PRINT);
		op = tag_token(token[0]);
		if (op)
			ft_token_add_end(&ms->head, ft_token_new(token, op));
		else
			clean_strlist(&token);
		i++;
	}
	clean_strlist(&pieces);
	return (ms->head);
}

t_types	tag_token(char *cmd)
{
	t_keyword_map	*keymap;

	keymap = (t_keyword_map[]){
	{">", OP_OUTPUT},
	{"<", OP_INPUT},
	{"<<", OP_UNTIL},
	{">>", OP_APPEND},
	{"|", OP_PIPE},
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
	while (i < NUM_SYMBOLS)
	{
		if (ft_strcmp(cmd, keymap[i].keyword) == 0)
			return (keymap[i].type);
		i++;
	}
	return (OP_CMD);
}
