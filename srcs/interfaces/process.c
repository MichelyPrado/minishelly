/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/12 13:29:03 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(t_sys_config *mini)
{
	close(mini->exec->fd[0][0]);
	close(mini->exec->fd[0][1]);
	close(mini->exec->fd[1][0]);
	close(mini->exec->fd[1][1]);
}

int	exec_program(t_sys_config *mini)
{
	if (mini->exec->flag == BFALSE)
		mini->exec->pid = fork();
	if (mini->exec->pid == 0)
	{
		cmd_path_valid(mini->tokens->token, mini->path);
		if (execve(*mini->tokens->token, mini->tokens->token, mini->env) == -1)
			sys_exit(clean_data, EACCES, mini);
		exit (0);
	}
	mini->exec->i++;
	return (0);
}

void	exec(t_sys_config *mini)
{
	int				status;
	t_process_func	*func;

	mini->exec = init_exec();
	func = (t_process_func *) mini->exec->func;
	while (mini->tokens)
	{
		func[mini->tokens->type](mini);
		mini->tokens = mini->tokens->next;
	}
	close_fds(mini);
	while (mini->exec->i)
	{
		waitpid(-1, &status, 0);
		mini->exec->i--;
	}
}
