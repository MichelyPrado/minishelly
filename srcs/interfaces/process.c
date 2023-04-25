/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/25 14:24:25 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	turn_void(t_sys_config *mini)
{
	printf("%i\n", mini->tokens->type);
	return (0);
}

int	exec_program(t_sys_config *mini)
{
	execve(*mini->tokens->token, mini->tokens->token, mini->env);
	return (0);
}

t_process_func	*array_functions(void)
{
	t_process_func	*array_process;

	array_process = (t_process_func *)malloc(sizeof(t_process_func) * 16);
	array_process[OP_DEFAULT] = turn_void;
	array_process[OP_AND] = turn_void;
	array_process[OP_OR] = turn_void;
	array_process[OP_PIPE] = ft_pipe;
	array_process[OP_OUTPUT] = turn_void;
	array_process[OP_INPUT] = turn_void;
	array_process[OP_UNTIL] = turn_void;
	array_process[OP_APPEND] = turn_void;
	array_process[OP_CMD] = exec_program;
	array_process[OP_EXIT] = ft_exit;
	array_process[OP_CD] = ft_cd;
	array_process[OP_ENV] = ft_env;
	array_process[OP_UNSET] = b_unset;
	array_process[OP_EXPORT] = b_export;
	array_process[OP_PWD] = ft_pwd;
	array_process[OP_ECHO] = ft_echo;
	return (array_process);
}

void	exec_commands(t_sys_config *mini)
{
	int				pid1;
	int				pid2;
	int				i = 0;
	//int				bkp[2];
	int				status;
	t_process_func	*array_process;

	pid1 = 0;
	pid2 = 0;
	//bkp[0] = dup(STDIN_FILENO);
	//bkp[1] = dup(STDOUT_FILENO);
	array_process = array_functions();
	if (mini->tokens->type == OP_CMD)
	{
		if (mini->tokens->next == NULL)
			;
		else if ((mini->tokens->next)->type == OP_PIPE)
			array_process[mini->tokens->next->type](mini);
		while (mini->tokens->next)
		{
			pid1 = fork();
			cmd_path_valid(mini->tokens->token, mini->path);
			if (pid1 == 0 && i == 0)
			{
				dup2(mini->fd[1], STDOUT_FILENO);
				close(mini->fd[0]);
				close(mini->fd[1]);
				array_process[mini->tokens->type](mini);
			}
			else if (pid1 == 0 && i == 1)
			{
				dup2(mini->fd[0], STDIN_FILENO);
				dup2(mini->fd[1], STDOUT_FILENO);
				close(mini->fd[1]);
				close(mini->fd[0]);
				array_process[mini->tokens->type](mini);
			}
			if (pid1 != 0)
				i = 1;
			mini->tokens = mini->tokens->next->next;
		}
		pid1 = fork();
		cmd_path_valid(mini->tokens->token, mini->path);
		if (pid1 == 0)
		{
			if (i == 1)
			{
				dup2(mini->fd[0], STDIN_FILENO);
				close(mini->fd[0]);
				close(mini->fd[1]);
			}
			array_process[mini->tokens->type](mini);
		}
		if (pid1 != 0 && i == 1)
		{
			close(mini->fd[0]);
			close(mini->fd[1]);
		}
		waitpid(pid1, &status, 0);
	}
	return ;
}


		// if (tokens->type == OP_CMD && !cmd_path_valid(tokens->token, mini->path))
		// {	
		// 	pid = fork();
		// 	if (pid == 0)
		// 	{
		// 		if (tokens->next && (tokens->next)->type == OP_PIPE)
		// 			array_process[tokens->next->type](mini);
		// 		else
		// 		{
		// 			dup2(bkp[0], STDIN_FILENO);
		// 			dup2(bkp[1], STDOUT_FILENO);
		// 		}
		// 		if (f == 0)
		// 		{
		// 			dup2(mini->fd[0], STDIN_FILENO);
		// 			dup2(mini->fd[1], STDOUT_FILENO);
		// 		} 
		// 		array_process[tokens->type](mini);
		// 	}
		// 	waitpid(pid, &status, 0);
		// 	if (tokens->next)
		// 		tokens = tokens->next;
		// }
		// else
		// {
		// 	dup2(bkp[0], STDIN_FILENO);
		// 	dup2(bkp[1], STDOUT_FILENO);
		// 	array_process[tokens->type](mini);
		// } 
		// tokens = tokens->next;