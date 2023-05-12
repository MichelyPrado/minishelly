/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:44:49 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/12 13:40:30 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ctrl_d(t_sys_config *mini)
{
	printf("Você saiu do Minishelly!\n");
	clean_strlist(&mini->prompt);
	clean_strlist(&mini->env);
	clean_strlist(&mini->path);
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini->str)
		free(mini->str);
	if (mini)
		free(mini);
	exit(EXIT_SUCCESS);
}
