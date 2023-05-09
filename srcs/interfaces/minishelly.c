/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/09 19:16:23 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	args_check(int argc)
{
	if (argc != 1)
	{
		printf("Invalid number of arguments!\n");
		exit(EXIT_FAILURE);
	}
}

//função que faz a identificação dos tipos dos tokens
void	print_tokens_test(t_token *tokens)
{
	int	i;

	while (tokens)
	{
		i = 0;
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

int	minishelly(int argc, char **argv, char **environ)
{
	int				prop;
	//t_sa			sa;
	t_sys_config	*mini;

	//sa = (t_sa){0};
	//wait_signal(&sa);
	args_check(argc);
	if (!*argv)
		return (0);
	mini = start_sys(environ);
	prop = 0;
	//signal(SIGINT, sig_handler);
	signal(SIGINT, (void (*)(int))sig_handler);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		if (wait_input(mini, &prop, readline(mini->prompt[prop])))
			continue ;
		expand_symbol(&mini->new_parser, '$', mini->env);
		mini->tokens = ft_create_tokens(mini);
		exec_commands(mini);
		add_history(mini->str);
		ft_token_free(&mini->tokens);
		if (mini->new_parser)
			free(mini->new_parser);
		mini->new_parser = NULL;
		mini->nlen_parser = 0;
		free(mini->str);
		mini->str = NULL;
	}
	return (0);
}
