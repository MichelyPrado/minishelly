/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/26 13:53:27 by dapaulin         ###   ########.fr       */
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

void	x(t_sys_config *mini, t_process_func * array_process, int pid, int i, int j)
{
	if (pid == 0)
	{
		if (i % 2 == 0)
		{	
			if (!j)
				dup2(mini->fd[0][1], STDOUT_FILENO);
			dup2(mini->fd[1][0], STDIN_FILENO);
		}
		else 
		{
			if (!j)
				dup2(mini->fd[1][1], STDOUT_FILENO);
			dup2(mini->fd[0][0], STDIN_FILENO);
		}
		close(mini->fd[0][0]);
		close(mini->fd[0][1]);
		close(mini->fd[1][0]);
		close(mini->fd[1][1]);
		array_process[mini->tokens->type](mini);
		exit(127);
	}
}

void	recycle_pipe(t_sys_config *mini, int i)
{
	int	fd;

	if (i % 2 == 0)
		fd = 1;
	else
		fd = 0;
	close(mini->fd[fd][0]);
	close(mini->fd[fd][1]);
	pipe(mini->fd[fd]);
}

void	clean_functions(t_process_func *funcs)
{

	if (funcs)
		free(funcs);
}

void	exec_commands(t_sys_config *mini)
{
	int				pid1;
	int				i = 0;
	int				status;
	t_process_func	*array_process;

	pid1 = 0;
	array_process = array_functions();
	array_process[mini->tokens->next->type](mini);
	while (mini->tokens->next)
	{
		if (mini->tokens->type == OP_CMD)
		{
			pid1 = fork();
			cmd_path_valid(mini->tokens->token, mini->path);
			x(mini, array_process, pid1, i, 0);
		}
		recycle_pipe(mini, i);
		mini->tokens = mini->tokens->next->next;
		i++;
	}
	pid1 = fork();
	cmd_path_valid(mini->tokens->token, mini->path);
	x(mini, array_process, pid1, i, 1);
	close(mini->fd[0][0]);
	close(mini->fd[0][1]);
	close(mini->fd[1][0]);
	close(mini->fd[1][1]);
	waitpid(pid1, &status, 0);
	clean_functions(array_process);
	return ;
}
