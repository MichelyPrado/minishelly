/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 23:37:20 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	finish_process(t_sys_config *ms, int err)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (err)
		ft_print_perr(*get_status_code(), NULL);
	close_pipes_fds(ms);
	while (i < ms->exec->i)
	{
		waitpid(ms->exec->pid[i], &status, 0);
		if (WIFEXITED(status))
			set_status_code(WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			*get_status_code() = 128 + WTERMSIG(status);
		i++;
	}
	wait_signal();
	*get_is_fork() = 0;
	clean_exec(&ms->exec);
}

void	exec(t_sys_config *mini)
{
	int				err;
	t_process_func	*func;

	mini->exec = init_exec();
	func = (t_process_func *) mini->exec->func;
	err = 0;
	while (mini->tokens)
	{
		*get_ms() = mini;
		if (mini->tokens->type == OP_PIPE)
			has_heredoc(mini->tokens->next, mini->env);
		else if (!mini->exec->i)
			has_heredoc(mini->tokens, mini->env);
		err = func[mini->tokens->type](mini);
		if (err || !mini->tokens)
			break ;
		mini->tokens = mini->tokens->next;
	}
	finish_process(mini, err);
}

void	clean_end_cmd(t_sys_config *ms)
{
	clean_no_exec(ms);
	clean_exec(&ms->exec);
}
