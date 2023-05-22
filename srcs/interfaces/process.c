/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/21 21:37:33 by dapaulin         ###   ########.fr       */
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
	int	err;

	err = 0;
	if (mini->exec->flag == BFALSE)
		mini->exec->pid = fork();
	if (mini->exec->pid == 0)
	{
		err = cmd_path_valid(mini->tokens->token, mini->path);
		if (err == -1)
		{
			if ((*mini->tokens->token[0] == '/' || !ft_strncmp(*mini->tokens->token, "..", 2) || !ft_strncmp(*mini->tokens->token, "./", 2)))
				set_status_code(126);
			sys_exit_err(clean_data, mini, " Permission denied");
		}
		if (!(*mini->tokens->token[0] == '/' || !ft_strncmp(*mini->tokens->token, "..", 2) || !ft_strncmp(*mini->tokens->token, "./", 2)))
			;
		else if (is_directory(*mini->tokens->token) == 1)
		{
			set_status_code(126);
			sys_exit_err(clean_data, mini, " Is a directory");
		}
		if (execve(*mini->tokens->token, mini->tokens->token, mini->env) == -1)
		{
			set_status_code(127);
			sys_exit_err(clean_data, mini, " command not found");
		}
		exit (0);
	}
	mini->exec->i++;
	return (0);
}

void	exec(t_sys_config *mini)
{
	int				i;
	int				err;
	static int		status;
	t_process_func	*func;

	mini->exec = init_exec();
	func = (t_process_func *) mini->exec->func;
	err = 0;
	while (mini->tokens)
	{
		err = func[mini->tokens->type](mini);
		if (err)
			break ;
		mini->tokens = mini->tokens->next;
	}
	if (err)
		ft_print_err(*get_status_code(), " vovozona\n");
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
