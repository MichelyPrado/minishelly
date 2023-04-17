/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/17 20:33:37 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


process_function   *array_functions()
{
    process_function *array_process;

    array_process = (process_function *)malloc(sizeof(process_function) * 13);
    array_process[10] = ft_cd;
    array_process[11] = ft_env;
    array_process[14] = ft_pwd;
    array_process[15] = ft_echo;
    return (array_process);
}

void    exec_commands(t_sys_config *mini)
{
    process_function *array_process;

    array_process = array_functions();
    if (mini->tokens->type == 8)
        fork();
    array_process[mini->tokens->type](mini);
    printf("aqui varia\n");
    return ;
}