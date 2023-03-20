/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:21:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/20 16:49:54 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_minishelly *mini, char *key)
{
	int		len;
	char	**aux;

	len = 0;
	if (!key || !mini->e)
		return ;
	if (search_envp(mini->e, key) < 0)
		return ;
	len = count_envp_items(mini->e);
	aux = (char **) ft_calloc(sizeof(char *), len + 1);
	slice_unset(mini, key, aux);
	clean_env(mini->e);
	mini->e = aux;
}

void	slice_unset(t_minishelly *mini, char *key, char **aux)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
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
}

void	add_envp_item(t_minishelly *mini, char *key, char *value)
{
	char	**aux;
	int		amount;

	if (!key)
		return ;
	if (!mini->e)
	{
		mini->e = (char **) ft_calloc(sizeof(char *), 2);
		mini->e[0] = join_key_value(key, value);
		return ;
	}
	else if (search_envp(mini->e, key) >= 0)
	{
		edit_envp(mini, key, value);
		return ;
	}
	amount = count_envp_items(mini->e);
	aux = (char **) ft_calloc(sizeof(char *), amount + 2);
	if (!aux)
		return ;
	slice_add(mini, aux, key, value);
}

void	slice_add(t_minishelly *mini, char **aux, char *key, char *value)
{
	int		i;

	i = 0;
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
