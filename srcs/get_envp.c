/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:39:24 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/07 16:39:13 by dapaulin         ###   ########.fr       */
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

void    split_paths(char **env, t_minishelly *data)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	data->path = ft_split((*env + 5), ':');
}

void    get_envp(char **envp, t_minishelly *data)
{
	int i;

	i = 0;
	data->e = (char **)ft_calloc(sizeof(char *), count_str_envp(envp) + 1);
    while(envp[i])
    {
        data->e[i] = ft_strdup(envp[i]);
        i++;
    }
}
