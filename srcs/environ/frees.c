/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 20:29:10 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 15:46:42 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	clean_sys(t_sys_config *mini)
{
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini->str)
		free(mini->str);
	close_fds(mini);
	clean_exec(&mini->exec);
	clean_strlist(&(mini->env));
	clean_strlist(&(mini->prompt));
	ft_token_free(&(mini->head));
	clean_strlist(&(mini->path));
	if (mini)
		free(mini);
}

void	clean_exec(t_exec **exec)
{
	int	i;

	i = 0;
	if ((*exec))
	{
		if ((*exec)->fd)
		{
			while (i < *get_num_pipes())
				free((*exec)->fd[i++]);
			free((*exec)->fd);
		}
		free((*exec)->func);
		free((*exec));
		(*exec) = NULL;
	}
}

void	clean_data(t_sys_config *mini)
{
	if (mini)
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
	}
}

void	clean_no_exec(t_sys_config *ms)
{
	set_num_pipes(0);
	ft_token_free(&ms->head);
	if (ms->new_parser)
		free(ms->new_parser);
	ms->new_parser = NULL;
	ms->nlen_parser = 0;
	if (ms->str)
		free(ms->str);
	ms->str = NULL;
}

void	clean_end_cmd(t_sys_config *ms)
{
	clean_no_exec(ms);
	clean_exec(&ms->exec);
}
