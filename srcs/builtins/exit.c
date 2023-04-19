/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:53:08 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_sys_config *mini)
{
	printf("Você saiu do Minishelly!\n");
	exit(EXIT_SUCCESS);
	mini->env = 0;
}
