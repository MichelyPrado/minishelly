/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:21:24 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/15 23:21:08 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo(t_sys_config *mini)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (mini->tokens->token[1])
	{
		if (ft_strcmp(mini->tokens->token[i], "-n") == 0 && i++)
			new_line = 0;
		while (mini->tokens->token[i] != NULL)
		{
			ft_printf("%s", mini->tokens->token[i]);
			if (mini->tokens->token[i + 1])
				ft_printf(" ");
			i++;
		}
	}
	if (new_line == 1)
		ft_printf("\n");
	return (0);
}
