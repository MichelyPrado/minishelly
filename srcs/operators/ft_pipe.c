/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:31:23 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/14 15:02:04 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	recycle_pipe(t_sys_config *mini)
{
	int	fd;

	if (mini->exec->i % 2 == 0)
		fd = 1;
	else
		fd = 0;
	close(mini->exec->fd[fd][0]);
	close(mini->exec->fd[fd][1]);
	pipe(mini->exec->fd[fd]);
}

void	make_dup2(t_sys_config *ms, int in, int out)
{
	if (ms->n_pip > 0)
	{
		if (dup2(ms->exec->fd[in][1], STDOUT_FILENO) == -1)
			sys_exit(clean_data, EBADF, ms);
	}
	if (dup2(ms->exec->fd[out][0], STDIN_FILENO))
		sys_exit(clean_data, EBADF, ms);
}

void	choice_dup2(t_sys_config *ms)
{
	if (ms->exec->i % 2 == 0)
		make_dup2(ms, 0, 1);
	else
		make_dup2(ms, 1, 0);
}

int	ft_pipe(t_sys_config *mini)
{
	t_process_func	*func;

	func = (t_process_func *) mini->exec->func;
	mini->exec->pid = fork();
	if (mini->tokens->next)
		mini->tokens = mini->tokens->next;
	if (mini->exec->pid == 0)
	{
		mini->exec->flag = BTRUE;
		choice_dup2(mini);
		close_fds(mini);
		func[mini->tokens->type](mini);
	}
	recycle_pipe(mini);
	mini->n_pip--;
	mini->exec->i++;
	return (0);
}
