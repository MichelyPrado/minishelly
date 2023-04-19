/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:35:26 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/18 05:12:20 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	b_unset(t_sys_config *mini)
{
	ft_unset(mini, mini->tokens->token[1]);
	printf("\n%s\n", mini->tokens->token[1]);
	return (0);
}
