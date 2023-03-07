/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 23:21:09 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/06 17:47:33 by msilva-p         ###   ########.fr       */
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

void get_envp(char **envp, t_minishelly *data)
{
	int i;

	i = 0;
	data->e = (char **)malloc(sizeof(char *));
	while(envp[i])
	{
		data->e[i] = ft_strdup(envp[i]);
		// printf("%s\n", data->e[i]);
		i++;
	} 
	i = 0;
	// while(data->e[i])
	// {
	// 	free(data->e[i]);
	// 	//printf("%s\n", data->e[i]);
	// 	i++;
	// }
	
}

int main(int argc, char **argv, char **envp)
{
	t_minishelly	data;

	args_check(argc);
	get_envp(envp, &data);
	while (1)
	{
		data.str = readline("Minishelly: ");
		add_history(data.str);
		exit_check(data.str);
	}
	return (0);
}