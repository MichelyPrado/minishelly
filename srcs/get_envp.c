/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:39:24 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/13 16:32:42 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_str_envp(char **envp)
{
	int	len;

	len = 0;
	while (*envp != NULL && envp[len])
		len++;
	return (len);
}

void	split_paths(char **env, t_minishelly *data)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	data->path = ft_split((*env + 5), ':');
}

void	delete_envp_item(t_minishelly *mini, char *str)
{
	int		qtt_envp;
	char	**aux;
	int		i;
	int		len;
	int		j;
	
	j = 0;
	qtt_envp = count_str_envp(mini->e);
	len = 0;
	i = 0;
	aux = (char**)ft_calloc(sizeof(char*), qtt_envp);
	while (mini->e[i + j])
	{
		if (ft_strncmp(mini->e[i + j], str, len) == 0)
			j = 1;
		aux[i] = ft_strdup(mini->e[i + j]);
		i++;	
	}
	clean_env(mini->e);
	mini->e = aux;
	
}

void	clean_env(char **new_envp)
{
	int	i;

	i = 0;
	while (new_envp[i])
	{
		free(new_envp[i]);
		i++;
	}
	free(new_envp);
}

void	get_envp(char **envp, t_minishelly *data)
{
	int	i;

	i = 0;
	data->e = (char **)ft_calloc(sizeof(char *), count_str_envp(envp) + 1);
	while (envp[i])
	{
		data->e[i] = ft_strdup(envp[i]);
		i++;
	}
}
