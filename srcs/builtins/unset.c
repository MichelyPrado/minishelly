/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:35:26 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/16 21:57:31 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_unset(t_sys_config *mini)
{
	if (mini->tokens->token[1])
	{
		ft_unset(mini, mini->tokens->token[1]);
		update_unbound_vars(mini->tokens->token[1], mini);
	}	
	set_status_code(0);
	return (0);
}
