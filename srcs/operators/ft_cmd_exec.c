/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:49:26 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 22:59:18 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	valid_permission_denied(t_sys_config *mini, int err)
{
	err = cmd_path_valid(mini->tokens->token, mini->path);
	if (err == -1)
	{
		if ((*mini->tokens->token[0] == '/' \
		|| !ft_strncmp(*mini->tokens->token, "..", 2) \
		|| !ft_strncmp(*mini->tokens->token, "./", 2)))
			set_status_code(126);
		sys_exit_err(clean_for_exec, mini, " Permission denied");
	}
}

void	valid_directory(t_sys_config *mini)
{
	if (!(*mini->tokens->token[0] == '/' \
	|| !ft_strncmp(*mini->tokens->token, "..", 2) \
	|| !ft_strncmp(*mini->tokens->token, "./", 2)))
		;
	else if (is_directory(*mini->tokens->token) == 1)
	{
		set_status_code(126);
		sys_exit_err(clean_for_exec, mini, " Is a directory");
	}
	close_bkp_terms_fds();
}

int	exec_program(t_sys_config *mini)
{
	int	err;

	err = 0;
	wait_signal_shield();
	*get_is_fork() = 1;
	if (mini->exec->flag == BFALSE)
		mini->exec->pid[mini->exec->i] = fork();
	if (mini->exec->pid[mini->exec->i] == 0)
	{
		valid_permission_denied(mini, err);
		valid_directory(mini);
		if (execve(*mini->tokens->token, mini->tokens->token, mini->env) == -1)
		{
			set_status_code(127);
			sys_exit_err(clean_for_exec, mini, " command not found");
		}
	}
	mini->exec->i++;
	return (0);
}
