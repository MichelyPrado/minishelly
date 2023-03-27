/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/27 19:42:16 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_check(char *str)
{
	if (strncmp(str, "exit", strlen(str) - 1) == 0)
	{
		printf("Você saiu do Minishelly!\n");
		exit(EXIT_SUCCESS);
	}
}

static void	args_check(int argc)
{
	if (argc != 1)
	{
		printf("Invalid number of arguments!\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_sys_config	mini;
	char			**token;

	args_check(argc);
	if (!*argv)
		return (0);
	token = NULL;
	mini = (t_sys_config){0};
	get_envp(envp, &mini);
	while (1)
	{
		mini.str = readline("Minishelly: ");
		symbol_delimiter(mini.str, &mini);
		if (mini.new_parser)
		token = ft_split(mini.new_parser, -1);
		while (*token)
		{
			printf("\n'%s'\n", *token);
			token++;
		}
		add_history(mini.str);
		exit_check(mini.str);
	}
	return (0);
}
