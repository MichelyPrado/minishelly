/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/16 18:59:16 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_fds(t_sys_config *mini)
{
	int	i;

	i = 0;
	while (mini->exec->fd && i < *get_num_pipes())
	{
		close(mini->exec->fd[i][0]);
		close(mini->exec->fd[i][1]);
		i++;
	}
}

int	exec_program(t_sys_config *mini)
{
	if (mini->exec->flag == BFALSE)
		mini->exec->pid = fork();
	if (mini->exec->pid == 0)
	{
		if (cmd_path_valid(mini->tokens->token, mini->path))
			sys_exit_err(clean_data, 127, mini," command not found");
		else if (execve(*mini->tokens->token, mini->tokens->token, mini->env) == -1)
			sys_exit_err(clean_data, EACCES, mini, " command not found");
		exit (0);
	}
	mini->exec->i++; 
	return (0);
}

void	exec(t_sys_config *mini)
{
	int				i;
	static int		status;
	t_process_func	*func;

	mini->exec = init_exec();
	func = (t_process_func *) mini->exec->func;
	while (mini->tokens)
	{
		func[mini->tokens->type](mini);
		mini->tokens = mini->tokens->next;
	}
	i = 0;
	close_fds(mini);
	while (i < mini->exec->i)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			set_status_code(WEXITSTATUS(status));
		i++;
	}
}
