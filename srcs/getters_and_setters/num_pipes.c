/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:49:53 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/16 15:49:56 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int *get_num_pipes()
{
    static int  num;

    return (&num);
}

void set_num_pipes(int num)
{
    int *sc;

    sc = get_status_code();
    *sc = num;
}