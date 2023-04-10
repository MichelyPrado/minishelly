/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:57 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/10 01:12:44 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// receber uma string separada por *
// while que percore a string contando os caracteres e
// quando achar um * ft_substr(new_parser, pos_inicial, qtd de caracteres)
// criar um node e armazenar o comando dentro
// passa para o proximo node
// repete até a string acabar
t_token *ft_create_tokens(t_sys_config *mini)
{
    return (NULL);
}

int ft_isspace(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] == '\t' || str[i] == ' '))
            return (0);
        i++;
    }
    return (1);
}

t_types tag_token(char *cmd)
{
    int size;

    size = ft_strlen(cmd);
    if (!cmd || ft_isspace(cmd))
        return (OP_DEFAULT);
    if (ft_strncmp(cmd, "&&", size) == 0)
        return (1);
    else if (ft_strncmp(cmd, "|", size) == 0)
        return (3);
    else if (ft_strncmp(cmd, "||", size) == 0)
        return (2);
    else if (ft_strncmp(cmd, ">", size) == 0)
        return (4);  
    else if (ft_strncmp(cmd, "<", size) == 0)
        return (5);
    else if (ft_strncmp(cmd, "<<", size) == 0)
        return (6);
    else if (ft_strncmp(cmd, ">>", size) == 0)
        return (7);
    else if (ft_strncmp(cmd, "exit", size) == 0)
        return (9);
    else if (ft_strncmp(cmd, "cd", size) == 0)
        return (10);
    else if (ft_strncmp(cmd, "env", size) == 0)
        return (11);
    else if (ft_strncmp(cmd, "unset", size) == 0)
        return (12);
    else if (ft_strncmp(cmd, "export", size) == 0)
        return (13);
    else if (ft_strncmp(cmd, "pwd", size) == 0)
        return (14);
    else if (ft_strncmp(cmd, "echo", size) == 0)
        return (15);
    return (8);
}


