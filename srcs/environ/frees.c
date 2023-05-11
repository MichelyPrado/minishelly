/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:29:10 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/11 16:22:20 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    clean_exec(t_exec **exec)
{
    if ((*exec))
	{
		if ((*exec)->fd[0])
			free((*exec)->fd[0]);
		if ((*exec)->fd[1])
			free((*exec)->fd[1]);
		if ((*exec)->fd)
			free((*exec)->fd);
		free((*exec)->func);
		free((*exec));
		(*exec) = NULL;
	}
}

void    clean_data(t_sys_config *mini)
{
    clean_strlist(&mini->prompt);
	clean_strlist(&mini->env);
	clean_strlist(&mini->path);
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini->str)
		free(mini->str);
	ft_token_free(&mini->tokens);
    clean_exec(&mini->exec);
	if (mini)
		free(mini);
}