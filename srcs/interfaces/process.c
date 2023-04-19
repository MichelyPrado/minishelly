/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:38:03 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:48:47 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	turn_void(t_sys_config *mini)
{
	printf("%i\n", mini->tokens->type);
	return (0);
}

t_process_function	*array_functions(void)
{
	t_process_function	*array_process;

	array_process = (t_process_function *)malloc(sizeof(t_process_function) * 16);
	array_process[0] = turn_void;
	array_process[1] = turn_void;
	array_process[2] = turn_void;
	array_process[3] = turn_void;
	array_process[4] = turn_void;
	array_process[5] = turn_void;
	array_process[6] = turn_void;
	array_process[7] = turn_void;
	array_process[8] = turn_void;
	array_process[9] = ft_exit;
	array_process[10] = ft_cd;
	array_process[11] = ft_env;
	array_process[12] = b_unset;
	array_process[13] = b_export;
	array_process[14] = ft_pwd;
	array_process[15] = ft_echo;
	return (array_process);
}

void	exec_commands(t_sys_config *mini)
{
	t_process_function	*array_process;

	array_process = array_functions();
	array_process[mini->tokens->type](mini);
	return ;
}
