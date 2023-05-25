/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:31:23 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/25 16:24:57 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	choice_dup2(t_sys_config *ms)
{
	if (ms->exec->i == 0)
	{
		if (dup2(ms->exec->fd[ms->exec->i][1], 1) == -1)
			sys_exit(clean_for_exec, EBADF, ms);
		return ;
	}
	else if (ms->exec->i == *get_num_pipes())
	{
		if (dup2(ms->exec->fd[ms->exec->i -1][0], 0) == -1)
			sys_exit(clean_for_exec, EBADF, ms);
		return ;
	}
	if (dup2(ms->exec->fd[ms->exec->i - 1][0], STDIN_FILENO) == -1)
		sys_exit(clean_for_exec, EBADF, ms);
	if (dup2(ms->exec->fd[ms->exec->i][1], STDOUT_FILENO) == -1)
		sys_exit(clean_for_exec, EBADF, ms);
}

static void	run_until(t_sys_config *ms)
{
	while (ms->tokens && ms->tokens->type >= OP_OUTPUT \
	&& ms->tokens->type <= OP_APPEND)
		ms->tokens = ms->tokens->next;
}

int	ft_pipe(t_sys_config *mini)
{
	t_process_func	*func;

	*get_is_fork() = 1 ;
	func = (t_process_func *) mini->exec->func;
	if (mini->tokens->next)
	{
		mini->exec->pid = fork();
		mini->tokens = mini->tokens->next;
	}
	if (mini->exec->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		mini->exec->flag = BTRUE;
		choice_dup2(mini);
		close_pipes_fds(mini);
		if (func[mini->tokens->type](mini))
			sys_exit_err(clean_for_exec, mini, NULL);
		clean_for_exec(mini);
		exit (0);
	}
	else
		run_until(mini);
	mini->exec->i++;
	return (0);
}
