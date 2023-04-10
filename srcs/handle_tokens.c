/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:57 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/10 16:43:59 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// receber uma string separada por *
// while que percore a string contando os caracteres e
// quando achar um * ft_substr(new_parser, pos_inicial, qtd de caracteres)
// criar um node e armazenar o comando dentro
// passa para o proximo node
// repete até a string acabar
t_token	*ft_create_tokens(t_sys_config *mini)
{
	int		i;
	t_types	op;
	t_token *tokens;
	char	**token;
	char	**pieces;
	
	i = 0;
	pieces = ft_split(mini->new_parser, NO_PRINT);
	tokens = (t_token *) {0};
	while (pieces[i])
	{
		token = ft_split(pieces[i], ' ');
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
	int	size;

	size = ft_strlen(cmd);
	if (!cmd || ft_isspace(cmd))
		return (OP_DEFAULT);
	if (ft_strncmp(cmd, "&&", size) == 0)
		return (OP_AND);
	else if (ft_strncmp(cmd, "|", size) == 0)
		return (OP_PIPE);
	else if (ft_strncmp(cmd, "||", size) == 0)
		return (OP_OR);
	else if (ft_strncmp(cmd, ">", size) == 0)
		return (OP_OUTPUT);
	else if (ft_strncmp(cmd, "<", size) == 0)
		return (OP_INPUT);
	else if (ft_strncmp(cmd, "<<", size) == 0)
		return (OP_UNTIL);
	else if (ft_strncmp(cmd, ">>", size) == 0)
		return (OP_APPEND);
	else if (ft_strncmp(cmd, "exit", size) == 0)
		return (OP_EXIT);
	else if (ft_strncmp(cmd, "cd", size) == 0)
		return (OP_CD);
	else if (ft_strncmp(cmd, "env", size) == 0)
		return (OP_ENV);
	else if (ft_strncmp(cmd, "unset", size) == 0)
		return (OP_UNSET);
	else if (ft_strncmp(cmd, "export", size) == 0)
		return (OP_EXPORT);
	else if (ft_strncmp(cmd, "pwd", size) == 0)
		return (OP_PWD);
	else if (ft_strncmp(cmd, "echo", size) == 0)
		return (OP_ECHO);
	return (OP_CMD);
}
