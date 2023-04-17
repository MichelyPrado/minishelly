/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/17 16:08:49 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    env(t_sys_config *mini)
{
    int i;

    i = 0;
    while (mini->env[i])
    {
        printf("%s\n", mini->env[i]);
        i++;
    }
    return (0);
}

process_function   *array_functions()
{
    process_function *array_process;

    array_process = (process_function *)malloc(sizeof(process_function) * 13);
    array_process[11] = env;
    return (array_process);
}

void    exec_commands(t_sys_config *mini)
{
    process_function *array_process;

    array_process = array_functions();
    array_process[mini->tokens->type](mini);
    return ;
}