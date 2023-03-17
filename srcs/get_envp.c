/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:39:24 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/17 18:37:40 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp_items(char **envp)
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
	int		i;
	int		j;
	int		len;
	char	**aux;
	int		amount_items;

	i = 0;
	j = 0;
	len = 0;
	if (!str || !mini->e)
		return ;
	amount_items = count_envp_items(mini->e);
	aux = (char **) ft_calloc(sizeof(char *), amount_items);
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

void	add_envp_item(t_minishelly *mini, char *key, char *value)
{
	int		i;
	int		len;
	char	**aux;
	int		all_values;

	i = 0;
	len = 0;
	if (!key || !mini->e)
		return ;
	all_values = count_envp_items(mini->e);
	aux = (char **) ft_calloc(sizeof(char *), all_values + 2);
	while (mini->e[i])
	{
		aux[i] = ft_strdup(mini->e[i]);
		i++;
	}
	clean_env(mini->e);
	mini->e = aux;
	len = (ft_strlen(key) + ft_strlen(value) + 2);
	mini->e[i] = ft_calloc(sizeof(char), len);
	ft_strlcat(mini->e[i], key, len);
	ft_strlcat(mini->e[i], "=", len);
	ft_strlcat(mini->e[i], value, len);
}

size_t	search_envp(char **envp, char *key)
{
	int		len;
	char	*p;

	len = 0;
	p = NULL;
	if (!key || !envp)
		return (0);
	while (*envp != NULL && envp[len])
	{
		p = ft_strchr(envp[len], '=');
		if (p == NULL)
			break ;
		if (ft_strncmp(envp[len], key, p - envp[len]) == 0)
			return (len);
		len++;	
	}
	return (0);
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
	data->e = (char **)ft_calloc(sizeof(char *), count_envp_items(envp) + 1);
	while (envp[i])
	{
		data->e[i] = ft_strdup(envp[i]);
		i++;
	}
}
