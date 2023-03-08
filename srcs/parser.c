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
    int     pipes;

    i = 0;
    c_pipe = 0;
    if (str == NULL)
        return (NULL);
    pipes = count_pipes(str, c);
    s = ft_calloc(sizeof(char), pipes + 1);
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
    return (s);
}

int    count_pipes(char *str, char c)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (str == NULL)
        return (0);
    while(str[i])
    {
        if (str[i] == '|')
        {
            j += 2;
        }
        i++;
    }
    return (i + j);
}