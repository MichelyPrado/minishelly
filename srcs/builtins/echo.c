/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:21:24 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/18 05:10:28 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_sys_config *mini)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 1;
	if (ft_strcmp(mini->tokens->token[i], "-n") == 0)
	{
		new_line = 0;
		i++;
	}
	while (mini->tokens->token[i])
	{
		printf("%s", mini->tokens->token[i]);
		if (mini->tokens->token[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 1)
		printf("\n");
	return (0);
}
