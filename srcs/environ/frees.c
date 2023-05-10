/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:29:10 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/09 20:32:24 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    clean_exec(t_exec **exec)
{
    if ((*exec))
	{
		int i = 0;
		while (i < (*exec)->pipes)
		{
			if ((*exec)->fd[i])
				free((*exec)->fd[i]);
			i++;
		}
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