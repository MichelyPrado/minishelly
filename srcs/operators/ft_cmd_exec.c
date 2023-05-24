/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:49:26 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 16:45:55 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_program(t_sys_config *mini)
{
	int	err;

	err = 0;
	if (mini->exec->flag == BFALSE)
		mini->exec->pid = fork();
	if (mini->exec->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		err = cmd_path_valid(mini->tokens->token, mini->path);
		if (err == -1)
		{
			if ((*mini->tokens->token[0] == '/' \
			|| !ft_strncmp(*mini->tokens->token, "..", 2) \
			|| !ft_strncmp(*mini->tokens->token, "./", 2)))
				set_status_code(126);
			sys_exit_err(clean_sys, mini, " Permission denied");
		}
		if (!(*mini->tokens->token[0] == '/' \
		|| !ft_strncmp(*mini->tokens->token, "..", 2) \
		|| !ft_strncmp(*mini->tokens->token, "./", 2)))
			;
		else if (is_directory(*mini->tokens->token) == 1)
		{
			set_status_code(126);
			sys_exit_err(clean_sys, mini, " Is a directory");
		}
		if (execve(*mini->tokens->token, mini->tokens->token, mini->env) == -1)
		{
			set_status_code(127);
			sys_exit_err(clean_sys, mini, " command not found");
		}
		clean_sys(mini);
		set_status_code(0);
		exit (0);
	}
	mini->exec->i++;
	return (0);
}
