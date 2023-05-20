/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/19 23:04:37 by dapaulin         ###   ########.fr       */
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


t_token	*reorder_tokens(t_token *tokens)
{
	int		i = 0;
	//t_token	*tmp;
	t_token	*bkp;
	t_token	*back;
	//char	**token;

	bkp = tokens;
	back = NULL;
	tokens = bkp;
	while (tokens)
	{	
		if (tokens->next && tokens->next->type == OP_PIPE
			&& (!back || back->type != OP_PIPE))
		{
			if (!back)
				bkp = copy_token(back, &tokens, tokens->next);
			else 
				copy_token(back, &tokens, tokens->next);
			back = tokens->next;
			tokens = back;
		}
		else if (tokens->next && tokens->next->type == OP_OUTPUT
			&& ((tokens->type >= OP_CMD && tokens->type <= OP_ECHO) || tokens->type == OP_UNTIL))
			ft_swap_token(&bkp, &tokens, &tokens->next);
		else if (tokens->next && tokens->next->type == OP_APPEND
			&& (tokens->type >= OP_CMD && tokens->type <= OP_ECHO))
			ft_swap_token(&bkp, &tokens, &tokens->next);
		else if (tokens->next && tokens->next->type == OP_INPUT
			&& (tokens->type >= OP_CMD && tokens->type <= OP_ECHO))
			ft_swap_token(&bkp, &tokens, &tokens->next);
		else
		{
			back = tokens;
			tokens = tokens->next;
		}
		i++;
		if (i == 15)
			break ;
	}
	return (bkp);
}

int	count_pip(t_token *t)
{
	int	i;

	i = 0;
	while (t)
	{
		if (t->type == OP_PIPE)
			i++;
		t = t->next;
	}
	return (i);
}

int	minishelly(int argc, char **argv, char **environ)
{
	int				prop;
	t_sa			sa;
	t_sys_config	*mini;

	sa = (t_sa){0};
	wait_signal(&sa);
	args_check(argc);
	if (!*argv)
		return (0);
	mini = start_sys(environ);
	prop = 0;
	while (1)
	{
		if (wait_input(mini, &prop, readline(mini->prompt[prop])))
			continue ;
		mini->tokens = ft_create_tokens(mini);
		if (!mini->tokens)
			continue ;
		*get_num_pipes() = count_pip(mini->tokens);
		ft_handle_files(mini->tokens);
		mini->tokens = reorder_tokens(mini->tokens);
		//print_tokens_test(mini);
		exec(mini);
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
