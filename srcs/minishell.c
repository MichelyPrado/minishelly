/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/12 15:44:52 by dapaulin         ###   ########.fr       */
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
	char			*tmp;
	t_err			err;
	t_sys_config	mini;
	t_token			*tokens;

	err = 0;
	tmp = "";
	args_check(argc);
	if (!*argv)
		return (0);
	mini = (t_sys_config){0};
	get_envp(envp, &mini);
	char	*rotulo = create_prompt(6, L_GREEN, SHELLNAME, L_BLUE, " dapaulin", L_WHITE, PROP);
	while (1)
	{
		err = 0;
		mini.str = readline(rotulo);
		if (ft_strlen(tmp))
		{
			mini.str = ft_strjoin(tmp, mini.str);
			printf("\n%s\n", mini.str);
		}
		err = check_readline(mini.str, &mini);
		if (err == ERR_NOLINE)
			continue;
		else if (err == ERR_QUOTES)
		{
			tmp = mini.str;
			rotulo = "quote>";
			continue;
		}
		else
		{	
			rotulo = create_prompt(6, L_GREEN, SHELLNAME, L_BLUE, " dapaulin", L_WHITE, PROP);
			tmp = "";
		}
		tokens = ft_create_tokens(&mini);
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
		add_history(mini.str);
		exit_check(mini.str);
	}
	return (0);
}
