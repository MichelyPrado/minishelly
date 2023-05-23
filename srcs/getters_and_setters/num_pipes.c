/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:49:53 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 15:35:44 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*get_num_pipes(void)
{
	static int	num;

	return (&num);
}

void	set_num_pipes(int num)
{
	int	*sc;

	sc = get_num_pipes();
	*sc = num;
}
