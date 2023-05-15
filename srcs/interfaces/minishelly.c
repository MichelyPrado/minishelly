/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishelly.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/14 20:57:35 by dapaulin         ###   ########.fr       */
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

void	swap_tokens(t_token *bk, t_token **md, t_token *end)
{
	t_token	*tmp;

	tmp = *md;
	if (bk)
		bk->next = end;
	tmp->next = end->next;
	end->next = tmp;
	//*md = end;
}

void	copy_token(t_token *bk, t_token **md, t_token *end)
{
	t_token	*cpy;

	cpy = ft_token_new(end->token, end->type);
	if (bk)
		bk->next = cpy;
	cpy->next = *md;
	//*md = cpy;
}

char **ft_realloc(char **array)
{
	int		i;
	char	**tmp;

	i = 0;
	while (array[i])
		i++;
	tmp = ft_calloc(sizeof(char *), i);
	i = 1;
	while (array[i])
	{
		tmp[i - 1] = array[i];
		i++;
	}
	if (array)
		free(array);
	return (tmp);
}

void	correct_puts(t_token *md, t_token *end)
{
	char	**tmp;
	
	tmp = NULL;
	if (md->type >= 4 && md->type <= 7)
	{
		tmp = ft_calloc(sizeof(char *), 3);
		tmp[0] = md->token[0];
		tmp[1] = end->token[0];
		if (md->token)
			free(md->token);
		md->token = tmp;
		end->token = ft_realloc(end->token);
	}
}

//função que faz a identificação dos tipos dos tokens
void	print_tokens_test(t_token *tokens)
{
	int		i;
	t_token	*back;

	back = NULL;
	correct_puts(tokens, tokens->next);
	while (tokens)
	{
		i = 0;
		ft_printf("Operador: %i\n[", tokens->type);
		while (tokens->token[i])
		{
			ft_printf("'%s', ", tokens->token[i]);
			i++;
		}
		printf("]\n");
		tokens = tokens->next;
	}
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
		search_for_symbol(&mini->new_parser, '$', mini->env);
		mini->tokens = ft_create_tokens(mini);
		print_tokens_test(mini->tokens);
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
