/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 15:31:23 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/05 11:01:52 by dapaulin         ###   ########.fr       */
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
	if (!mini->exec->flag)
		dup2(mini->exec->fd[outfd][1], STDOUT_FILENO);
	dup2(mini->exec->fd[infd][0], STDIN_FILENO);
}

int ft_pipe(t_sys_config *mini)
{
	t_process_func	*func;

	func = (t_process_func *)mini->exec->func;
    cmd_path_valid(mini->tokens->token, mini->path);
	if (mini->exec->pid == 0)
	{
		if (mini->exec->i % 2 == 0)
			make_dup2(mini, 1, 0);
		else 
			make_dup2(mini, 0, 1);
        close_fds(mini);
		func[mini->tokens->type](mini);
		exit(127);
	}
    recycle_pipe(mini);
	mini->exec->i++;
    return (0);
}