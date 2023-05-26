/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:44:49 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 19:41:41 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_ctrl_d(t_sys_config *mini)
{
	printf("Você saiu do Minishelly!\n");
	rl_clear_history();
	close_files_fds();
	clean_strlist(&mini->prompt);
	clean_strlist(&mini->env);
	clean_strlist(&mini->path);
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini->str)
		free(mini->str);
	if (mini)
		free(mini);
	close_terms_fds();
	exit(EXIT_SUCCESS);
}
