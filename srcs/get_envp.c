/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:39:24 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/07 13:26:00 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int count_str_envp(char **envp)
{
    int len;
    
    len = 0;
    while(*envp != NULL && envp[len])
        len++;
    return(len);
}

void get_envp(char **envp, t_minishelly *data)
{
	int i;

	i = 0;
	data->e = (char **)calloc(sizeof(char *), count_str_envp(envp) + 1);
    while(envp[i])
    {
        data->e[i] = ft_strdup(envp[i]);
        i++;
    }
}
 