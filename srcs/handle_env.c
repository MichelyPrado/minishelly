/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:21:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/20 19:59:05 by msilva-p         ###   ########.fr       */
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
	alloc_envp(mini, 1);
	slice_unset(mini, key, aux);
	clean_env(mini->e);
	mini->e = aux;
}

void	ft_export(t_minishelly *mini, char *key, char *value)
{
	char	**aux;
	int		amount;

	if (!key)
		return ;
	if (!mini->e)
	{
		mini->e = (char **) ft_calloc(sizeof(char *), 2);
		mini->e[0] = ft_strjoin(key, value);
		return ;
	}
	else if (search_envp(mini->e, key) >= 0)
	{
		edit_envp(mini, key, value);
		return ;
	}
	alloc_envp(mini, 2);
	slice_add(mini, aux, key, value);
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
	if (!new_value)
		mini->e[i] = ft_strjoin(key, "");
	else
		mini->e[i] = ft_strjoin(key, new_value);
}

void	get_envp(char **envp, t_minishelly *data)
{
	int	i;

	i = 0;
	data->e = (char **)ft_calloc(sizeof(char *), count_vars(envp) + 1);
	while (envp[i])
	{
		data->e[i] = ft_strdup(envp[i]);
		i++;
	}
}
