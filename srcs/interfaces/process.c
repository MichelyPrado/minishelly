/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 16:26:57 by msilva-p         ###   ########.fr       */
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
	{	
		mini->exec->pid = fork();
	}
	if (mini->exec->pid == 0)
	{
		*get_is_fork() = 1;
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
			sys_exit_err(clean_sys, mini, " command not found :(");
		}
		clean_sys(mini);
		set_status_code(0);
		exit (0);
	}
	mini->exec->i++;
	return (0);
}

int	has_heredoc(t_token *t, char **env)
{
	int	has;

	has = 0;
	while (t && t->type != OP_PIPE)
	{
		if (t->type == OP_UNTIL)
			run_here_doc(t, env);	
		t = t->next;
	}
	return (has);
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
	i = 0;
	while (mini->tokens)
	{
		if (mini->tokens->type == OP_PIPE)
			has_heredoc(mini->tokens->next, mini->env);
		else
			has_heredoc(mini->tokens, mini->env);
		err = func[mini->tokens->type](mini);
		if (err || !mini->tokens)
			break ;
		mini->tokens = mini->tokens->next;
	}
	if (err)
		ft_print_err(*get_status_code(), " vovozona\n");
	close_fds(mini);
	while (i < mini->exec->i)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			set_status_code(WEXITSTATUS(status));
		i++;
	}
	*get_is_fork() = 0;
	clean_exec(&mini->exec);
}
