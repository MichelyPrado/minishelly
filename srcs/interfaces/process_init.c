/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 13:19:42 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 15:26:41 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	turn_void(t_sys_config *mini)
{
	printf("%i\n", mini->tokens->type);
	return (0);
}

t_exec	*init_exec(void)
{
	int		i;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->i = 0;
	exec->pid = 0;
	exec->fd = (int **) ft_calloc(*get_num_pipes(), sizeof(int *));
	i = 0;
	while (i < *get_num_pipes())
	{
		exec->fd[i] = malloc(2 * sizeof(int));
		pipe(exec->fd[i]);
		i++;
	}
	exec->flag = BFALSE;
	exec->func = array_functions();
	return (exec);
}

t_process_func	*array_functions(void)
{
	t_process_func	*array_process;

	array_process = (t_process_func *)malloc(sizeof(t_process_func) \
	* NUM_FUNCS);
	array_process[OP_DEFAULT] = turn_void;
	array_process[OP_OUTPUT] = ft_output;
	array_process[OP_INPUT] = ft_input;
	array_process[OP_UNTIL] = ft_heredoc;
	array_process[OP_APPEND] = ft_append;
	array_process[OP_PIPE] = ft_pipe;
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
