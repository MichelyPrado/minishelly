/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:31:23 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/27 20:20:40 by dapaulin         ###   ########.fr       */
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

int ft_pipe(t_sys_config *mini)
{
	t_process_func	*func;

	func = (t_process_func *)mini->exec->func;
    cmd_path_valid(mini->tokens->token, mini->path);
	if (mini->exec->pid == 0)
	{
		if (mini->exec->i % 2 == 0)
		{	
			if (!mini->exec->flag)
				dup2(mini->exec->fd[0][1], STDOUT_FILENO);
			dup2(mini->exec->fd[1][0], STDIN_FILENO);
		}
		else 
		{
			if (!mini->exec->flag)
				dup2(mini->exec->fd[1][1], STDOUT_FILENO);
			dup2(mini->exec->fd[0][0], STDIN_FILENO);
		}
        close_fds(mini);
		func[mini->tokens->type](mini);
		exit(127);
	}
    recycle_pipe(mini);
    return (0);
}