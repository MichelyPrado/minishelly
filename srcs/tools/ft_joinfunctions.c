/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_joinfunctions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 14:00:10 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/18 14:20:38 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **ft_listjoin(char **ls, char **lsd)
{
    int     i;
    int     j;
    char    **ret;

    ret = NULL;
    if (!ls && !lsd)
        return (NULL);
    if (!ls && lsd)
        return (lsd);
    if (!lsd && ls)
        return (ls);
    ret = ft_calloc(sizeof(char *), ft_listlen(ls) + ft_listlen(lsd) + 1);
    i = -1;
    while (ls[++i])
        ret[i] = ls[i];
    j = -1;
    while (lsd[++j])
        ret[i + j] = lsd[j];
    return (ret);
}