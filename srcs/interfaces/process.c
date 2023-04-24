/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/24 16:12:18 by msilva-p         ###   ########.fr       */
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
	int				pid;
	int				status;
	t_token			*tokens;
	t_process_func	*array_process;

	pid = 0;
	tokens = mini->tokens;
	array_process = array_functions();
	if (tokens->type == OP_CMD && !cmd_path_valid(tokens->token, mini->path))
		pid = fork();
	if (pid == 0)
		array_process[tokens->type](mini);
	waitpid(pid, &status, 0);
	return ;
}
