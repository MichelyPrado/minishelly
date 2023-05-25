/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 19:19:42 by msilva-p         ###   ########.fr       */
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
		ft_print_err(*get_status_code(), " vovozona\n");
	close_pipes_fds(ms);
	while (i < ms->exec->i)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			set_status_code(WEXITSTATUS(status));
		i++;
	}
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
		if (mini->tokens->type == OP_PIPE)
		{
			has_heredoc(mini->tokens->next, mini->env);
			//signal(SIGINT, sig_handler);

		}
		else
		{
			has_heredoc(mini->tokens, mini->env);
			//signal(SIGINT, sig_handler);
		}
		err = func[mini->tokens->type](mini);
		if (err || !mini->tokens)
			break ;
		mini->tokens = mini->tokens->next;
	}
	finish_process(mini, err);
}
