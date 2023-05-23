/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:31:23 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/22 19:29:35 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	choice_dup2(t_sys_config *ms)
{
	if (ms->exec->i == 0)
	{
		if (dup2(ms->exec->fd[ms->exec->i][1], 1) == -1)
			sys_exit(clean_data, EBADF, ms);
		return ;
	}
	else if (ms->exec->i == *get_num_pipes())
	{
		if (dup2(ms->exec->fd[ms->exec->i -1][0], 0) == -1)
			sys_exit(clean_data, EBADF, ms);
		return ;
	}
	if (dup2(ms->exec->fd[ms->exec->i - 1][0], STDIN_FILENO) == -1)
		sys_exit(clean_data, EBADF, ms);
	if (dup2(ms->exec->fd[ms->exec->i][1], STDOUT_FILENO) == -1)
		sys_exit(clean_data, EBADF, ms);
}

int	ft_pipe(t_sys_config *mini)
{
	t_process_func	*func;

	func = (t_process_func *) mini->exec->func;
	if (mini->tokens->next)
	{
		mini->exec->pid = fork();
			mini->tokens = mini->tokens->next;
	}
	if (mini->exec->pid == 0)
	{
		mini->exec->flag = BTRUE;
		choice_dup2(mini);
		close_fds(mini);
		if (func[mini->tokens->type](mini))
			exit(*get_status_code());
		clean_sys(mini);
		set_status_code(0);
		exit (0);
	}
	else
	{
		while (mini->tokens && mini->tokens->type >= OP_OUTPUT \
		&& mini->tokens->type <= OP_APPEND)
			mini->tokens = mini->tokens->next;
	}
	mini->exec->i++;
	return (0);
}
