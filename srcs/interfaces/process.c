/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/05 14:55:48 by dapaulin         ###   ########.fr       */
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

t_exec		*init_exec()
{
	int		i;
	t_exec	*exec;

	i = 0;
	exec = malloc(sizeof(t_exec));
	exec->i = 0;
	exec->pid = 0;
	exec->pipes = 3;
	exec->fd = (int **) malloc(exec->pipes * sizeof(int *));
	while (i < exec->pipes)
	{
		exec->fd[i] = malloc(2 * sizeof(int));
		pipe(exec->fd[i++]);
	}
	exec->status = 0;
	exec->flag = BFALSE;
	exec->func = array_functions();
	return (exec);
}

void	close_fds(t_sys_config *mini)
{
	close(mini->exec->fd[0][0]);
	close(mini->exec->fd[0][1]);
	close(mini->exec->fd[1][0]);
	close(mini->exec->fd[1][1]);
}

void	exec_commands(t_sys_config *mini)
{
	t_process_func	*func;

	mini->exec = init_exec();
	func = (t_process_func *) mini->exec->func;
	while (mini->tokens)
	{
		if (!mini->tokens->next)
			mini->exec->flag = BTRUE;
		if (mini->tokens->type == OP_CMD)
		{
			mini->exec->pid = fork();
			func[OP_PIPE](mini);
			if (mini->exec->flag == BTRUE)
				break;
			mini->tokens = mini->tokens->next;
		}
		mini->tokens = mini->tokens->next;
	}
	close_fds(mini);
	free(mini->exec->fd[0]);
	free(mini->exec->fd[1]);
	free(mini->exec->fd);
	if (mini->exec->pid)
		waitpid(mini->exec->pid, &mini->exec->status, 0);
	if (mini->exec->func)
		free(mini->exec->func);
	return ;
}
