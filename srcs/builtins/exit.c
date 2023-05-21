/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:12:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/21 13:47:09 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_sys_config *mini)
{
	long	err;

	err = 1;
	if (ft_listlen(mini->tokens->token) <= 2)
	{
		if (mini->tokens->token[1])
			err = ft_atoi(mini->tokens->token[1]);
		if (!err && (ft_strlen(mini->tokens->token[1]) > 2
				|| !ft_isdigit(*mini->tokens->token[1])))
		{
			if (!(ft_strlen(mini->tokens->token[1]) > 19))
			{
				err = 2;
				ft_print_err(2, " numeric argument required");
			}
		}
	}
	else
		ft_print_err(1, " too many arguments");
	clean_sys(mini);
	exit(err);
}
