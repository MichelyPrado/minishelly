/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/21 16:35:47 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_tokens_test(t_sys_config *ms);

static void	args_check(int argc, char **argv)
{
	if (argc != 1)
	{
		printf("Invalid number of arguments!\n");
		exit(EXIT_FAILURE);
	}
	if (!*argv)
		exit (0);
}

void	clean_end_cmd(t_sys_config *ms)
{
	clean_exec(&ms->exec);
	ft_token_free(&ms->tokens);
	if (ms->new_parser)
		free(ms->new_parser);
	ms->new_parser = NULL;
	ms->nlen_parser = 0;
	if (ms->str)
		free(ms->str);
	ms->str = NULL;
}

int	minishelly(int argc, char **argv, char **environ)
{
	int				prop;
	t_sa			sa;
	t_sys_config	*mini;

	sa = (t_sa){0};
	prop = 0;
	wait_signal(&sa);
	args_check(argc, argv);
	mini = start_sys(environ);
	while (1)
	{
		*get_num_pipes() = 0;
		if (wait_input(mini, &prop, readline(mini->prompt[prop])))
			continue ;
		mini->tokens = ft_create_tokens(mini);
		if (!mini->tokens)
			continue ;
		prepare_commands(mini);
		print_tokens_test(mini);
		exec(mini);
		add_history(mini->str);
		clean_end_cmd(mini);
	}
	return (0);
}


void	print_tokens_test(t_sys_config *ms)
{
	int		i;
	int		j = 0;
	t_token	*back;
	t_token *tokens;

	tokens = ms->tokens;
	back = NULL;
	while (tokens)
	{
		i = 0;
		ft_printf("Operador: %i\tnum pipes: %i\n[", tokens->type, *get_num_pipes());
		while (tokens->token[i])
		{
			ft_printf("'%s', ", tokens->token[i]);
			if (i == 15)
				break ;
			i++;
		}
		printf("]\n");
		tokens = tokens->next;
		j++;
		if (j == 15)
			exit (123);
	}
}
