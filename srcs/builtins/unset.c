/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:35:26 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/15 22:49:39 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_unset(t_sys_config *mini)
{
	ft_unset(mini, mini->tokens->token[1]);
	update_unbound_vars(mini->tokens->token[1], mini);
	return (0);
}
