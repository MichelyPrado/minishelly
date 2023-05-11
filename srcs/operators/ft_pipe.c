/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:31:23 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/11 13:05:57 by dapaulin         ###   ########.fr       */
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

void	make_dup2(t_sys_config *mini, int infd, int outfd)
{
	if (mini->exec->i != mini->exec->pipes)
		dup2(mini->exec->fd[outfd][1], STDOUT_FILENO);
	dup2(mini->exec->fd[infd][0], STDIN_FILENO);
}

int ft_pipe(t_sys_config *mini)
{
	t_process_func	*func;

	func = (t_process_func *) mini->exec->func;
	mini->exec->pid = fork();
	mini->tokens = mini->tokens->next;
	if (mini->exec->pid == 0)
	{
		mini->exec->flag = BTRUE;
		if (mini->exec->i % 2 == 0)
			dup2(mini->exec->fd[0][1], STDOUT_FILENO);
		else 
			dup2(mini->exec->fd[0][0], STDIN_FILENO);
        close_fds(mini);
		func[mini->tokens->type](mini);
		exit(0);
	}
	recycle_pipe(mini);
	mini->exec->i++;
    return (0);
}