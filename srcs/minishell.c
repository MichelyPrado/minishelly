/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:05:56 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exit_check(char *str)
{
	if (strncmp(str, "exit", strlen(str) - 1) == 0)
	{
		printf("Você saiu do Minishelly!\n");
		exit(EXIT_SUCCESS);
	}
}

static void args_check(int argc)
{
	if (argc != 1)
	{
		printf("Invalid number of arguments!\n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv, char **envp)
{
	t_minishelly	data;

	args_check(argc);
	if (!*argv)
		return (0);
	get_envp(envp, &data);
	while (1)
	{
		data.str = readline("Minishelly: ");
		add_history(data.str);
		exit_check(data.str);
	}
	return (0);
}