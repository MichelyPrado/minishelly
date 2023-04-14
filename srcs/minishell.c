/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/13 20:11:03 by dapaulin         ###   ########.fr       */
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

void	print_tokens_test(t_token *tokens)
{
	while (tokens)
	{
		int i = 0;
		printf("Operador: %i\n[", tokens->type);
		while (tokens->token[i])
		{
			printf("'%s', ", tokens->token[i]);
			i++;
		}
		printf("]\n");
		tokens = tokens->next;
	}
}

int	main(int argc, char **argv)
{
	char			*tmp;
	t_err			err;
	int				prop;
	t_sys_config	*mini;
	t_token			*tokens;

	err = 0;
	tmp = "";
	args_check(argc);
	if (!*argv)
		return (0);
	mini = start_sys();
	prop = 0;
	while (1)
	{
		if (wait_input(mini, &prop, readline(mini->prompt[prop])))
			continue;
		tokens = ft_create_tokens(mini);
		print_tokens_test(tokens);
		add_history(mini->str);
		exit_check(mini->str);
	}
	return (0);
}


