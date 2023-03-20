/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:21:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/18 17:29:47 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_envp_item(t_minishelly *mini, char *key)
{
	int		i;
	int		j;
	int		len;
	char	**aux;

	i = 0;
	j = 0;
	len = 0;
	if (!key || !mini->e)
		return ;
	if (search_envp(mini->e, key) < 0)
		return ;
	len = count_envp_items(mini->e);
	aux = (char **) ft_calloc(sizeof(char *), len + 1);
	while (mini->e[i + j])
	{
		len = keylen(mini->e[i]);
		if (ft_strncmp(mini->e[i + j], key, len) == 0)
			j = 1;
		if (!mini->e[i + j])
			break ;
		aux[i] = ft_strdup(mini->e[i + j]);
		i++;
	}
	clean_env(mini->e);
	mini->e = aux;
}

void	add_envp_item(t_minishelly *mini, char *key, char *value)
{
	int		i;
	char	**aux;
	int		amount;

	i = 0;
	if (!key)
		return ;
	if (!mini->e)
	{
		mini->e = (char **) ft_calloc(sizeof(char *), 2);
		mini->e[0] = join_key_value(key, value);
		return ;
	}
	else if (search_envp(mini->e, key) >= 0)
		return ;
	amount = count_envp_items(mini->e);
	aux = (char **) ft_calloc(sizeof(char *), amount + 2);
	if (!aux)
		return ;
	while (mini->e[i])
	{
		aux[i] = ft_strdup(mini->e[i]);
		i++;
	}
	clean_env(mini->e);
	mini->e = aux;
	mini->e[i] = join_key_value(key, value);
}

ssize_t	search_envp(char **envp, char *key)
{
	int		i;
	int		len;
	char	*p;

	i = 0;
	p = NULL;
	len = 0;
	if (!key || !envp)
		return (-1);
	while (envp[i])
	{
		len = keylen(envp[i]);
		if (ft_strncmp(envp[i], key, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

void	edit_envp(t_minishelly *mini, char *key, char *new_value)
{
	int	i;

	if (!mini->e || !key)
		return ;
	i = search_envp(mini->e, key);
	if (i < 0)
		return ;
	free(mini->e[i]);
	mini->e[i] = join_key_value(key, new_value);
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
