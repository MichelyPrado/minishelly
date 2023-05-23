/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/22 19:44:39 by msilva-p         ###   ########.fr       */
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

int	print_flow_msg(t_sys_config *ms, char *msg)
{
	ft_printf("syntax error near unexpected token '%s'\n", msg);
	add_history(ms->str);
	clean_no_exec(ms);
	return (1);
}

int	ft_valid_flow(t_sys_config *ms)
{
	t_token	*t;

	t = ms->tokens;
	if (!t)
		return (0);
	if (t->type == OP_PIPE)
		return (print_flow_msg(ms, "|"));
	while (t)
	{
		if ((t->type >= OP_OUTPUT && t->type <= OP_APPEND) && !t->next)
			return (print_flow_msg(ms, "newline"));
		else if (t->type == OP_PIPE && \
		(t->next->type == OP_OUTPUT || t->next->type == OP_APPEND))
			;
		else if ((t->type >= OP_OUTPUT && t->type <= OP_PIPE) \
		&& t->next && !(t->next->type >= OP_CMD \
		&& t->next->type <= OP_ECHO))
			return (print_flow_msg(ms, t->next->token[0]));
		t = t->next;
	}
	return (0);
}

int	minishelly(int argc, char **argv, char **environ)
{
	int				prop;
	t_sa			sa;
	t_sys_config	*mini;

	prop = 0;
	sa = (t_sa){0};
	wait_signal(&sa);
	args_check(argc, argv);
	mini = start_sys(environ);
	while (1)
	{
		if (wait_input(mini, &prop, readline(mini->prompt[prop])))
			continue ;
		mini->tokens = ft_create_tokens(mini);
		// Criar validador de entradas erradas.
		if (ft_valid_flow(mini))
			continue ;
		if (!mini->tokens)
		{
			add_history(mini->str);
			set_status_code(0);
			clean_no_exec(mini);
			continue ;
		}
		prepare_commands(mini);
		print_tokens_test(mini);
		exec(mini);
		add_history(mini->str);
		ft_token_free(&mini->head);
		clean_end_cmd(mini);
	}
	return (0);
}


void	print_tokens_test(t_sys_config *ms)
{
	int		i;
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
	}
}
