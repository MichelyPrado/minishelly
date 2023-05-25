/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/25 19:41:02 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (t && (t->type == OP_PIPE || t->token[0][0] == '|'))
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

static int	is_token_null(t_sys_config *ms)
{
	if (!ms->tokens)
	{
		add_history(ms->str);
		set_status_code(0);
		clean_no_exec(ms);
		return (1);
	}
	return (0);
}

int	minishelly(int argc, char **argv, char **environ)
{
	int				prop;
	t_sys_config	*mini;

	prop = 0;
	args_check(argc, argv);
	wait_signal();
	mini = start_sys(environ);
	while (1)
	{
		if (wait_input(mini, &prop, readline(mini->prompt[prop])))
			continue ;
		mini->tokens = ft_create_tokens(mini);
		if (ft_valid_flow(mini) || is_token_null(mini))
			continue ;
		prepare_commands(mini);
		exec(mini);
		add_history(mini->str);
		ft_token_free(&mini->head);
		clean_end_cmd(mini);
	}
	return (0);
}
