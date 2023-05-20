/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinfunctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:00:10 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/20 11:24:59 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **ft_listjoin(char **ls, char **lsd)
{
    int     i;
    int     j;
    char    **ret;

    ret = NULL;
    ret = ft_calloc(sizeof(char *), ft_listlen(ls) + ft_listlen(lsd) + 1);
    i = 0;
    while (ls && ls[i])
    {
        ret[i] = ls[i];
        i++;
    }
    j = 0;
    while (lsd && lsd[j])
    {
        ret[i + j] = lsd[j];
        j++;
    }
    return (ret);
}