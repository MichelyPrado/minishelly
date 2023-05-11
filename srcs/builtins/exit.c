/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/11 20:24:32 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_sys_config *mini)
{
	int	err;

	err = 0;
	printf("Você saiu do Minishelly!\n");
	if (mini->tokens->token[1])
		err = ft_atoi(mini->tokens->token[1]);
	clean_data(mini);
	exit(err);
}
