/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:57 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/03 16:02:25 by msilva-p         ###   ########.fr       */
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

t_types tag_token(char *cmd)
{
    if (ft_strncmp(cmd, "&&", ft_strlen(cmd)) == 0)
        return (1);
    else if (ft_strncmp(cmd, "|", ft_strlen(cmd)) == 0)
        return (3);
    else if (ft_strncmp(cmd, "||", ft_strlen(cmd)) == 0)
        return (2);
    else if (ft_strncmp(cmd, ">", ft_strlen(cmd)) == 0)
        return (4);  
    else if (ft_strncmp(cmd, "<", ft_strlen(cmd)) == 0)
        return (5);
    else if (ft_strncmp(cmd, "<<", ft_strlen(cmd)) == 0)
        return (6);
    else if (ft_strncmp(cmd, ">>", ft_strlen(cmd)) == 0)
        return (7);
    else if (ft_strncmp(cmd, "grep", ft_strlen(cmd)) == 0)
        return (8);
    else if (ft_strncmp(cmd, "exit", ft_strlen(cmd)) == 0)
        return (9);
    else if (ft_strncmp(cmd, "cd", ft_strlen(cmd)) == 0)
        return (10);
    else if (ft_strncmp(cmd, "env", ft_strlen(cmd)) == 0)
        return (11);
    else if (ft_strncmp(cmd, "unset", ft_strlen(cmd)) == 0)
        return (12);
    else if (ft_strncmp(cmd, "export", ft_strlen(cmd)) == 0)
        return (13);
    else if (ft_strncmp(cmd, "pwd", ft_strlen(cmd)) == 0)
        return (14);
    else if (ft_strncmp(cmd, "echo", ft_strlen(cmd)) == 0)
        return (15);
    else if (ft_strncmp(cmd, "       ", ft_strlen(cmd)) == 0)
        return (OP_DEFAULT);
    return (0);
}


