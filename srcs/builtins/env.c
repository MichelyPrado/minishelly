/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:17:06 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:53:05 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_env(t_sys_config *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
	{
		if (ft_strchr(mini->env[i], '='))
			ft_printf("%s\n", mini->env[i]);
		i++;
	}
	return (0);
}
