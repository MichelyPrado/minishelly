/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 16:11:18 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/07 17:05:00 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *split_pipe(char *str, char c)
{
    int     i;
    int     c_pipe;
    char    *s;

    i = 0;
    c_pipe = 0;
    if (str == NULL)
        return (NULL);
    s = ft_calloc(sizeof(char), ft_strlen(str) + 3);
    while(str[i])
    {
        if (str[i] == '|')
        {
            s[i + c_pipe] = c;
            c_pipe++;
            s[i + c_pipe] = str[i];
            c_pipe++;
            s[i + c_pipe] = c;
            i++;
        }
        s[i + c_pipe] = str[i];
        i++;
    }
    if (*str)
        free(str);
    return (s);
}