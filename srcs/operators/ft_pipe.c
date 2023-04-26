/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:31:23 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/25 21:14:31 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_pipe(t_sys_config *mini)
{
    int err;
    
    err = pipe(mini->fd[0]);
    if (err == -1)
        return (err);
    err = pipe(mini->fd[1]);
    return (err);
}