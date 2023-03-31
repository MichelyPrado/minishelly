/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:16:57 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/30 21:56:06 by msilva-p         ###   ########.fr       */
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
    if (ft_strncmp(cmd, "|", ft_strlen(cmd)) == 0)
        return (362);
    return (368);
}