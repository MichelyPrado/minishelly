/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:21:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/17 20:04:00 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Exclui a variavel informada caso ela
exista em env. */
void	ft_unset(t_sys_config *mini, char *key)
{
	int		i;
	int		j;
	char	**aux;

	i = 0;
	j = 0;
	if (!key || !mini->env)
		return ;
	if (search_envp(mini->env, key) < 0)
		return ;
	aux = alloc_env(mini->env, CHAR_NULL);
	while (mini->env[i + j])
	{
		if (ft_strncmp(mini->env[i + j], key, keylen(mini->env[i])) == 0)
			j = 1;
		if (!mini->env[i + j])
			break ;
		aux[i] = ft_strdup(mini->env[i + j]);
		i++;
	}
	clean_env(mini->env);
	mini->env = aux;
}

/* Cria uma nova variavel em env se não existir ou
edita caso exista. */
void	ft_export(t_sys_config *mini, char *key, char *value)
{
	int		i;
	char	**aux;

	if (!key)
		return ;
	if (env_empty(mini, key, value))
		return ;
	if (edit_envp(mini, key, value))
		return ;
	aux = alloc_env(mini->env, MORE_ONE_SPACE);
	i = 0;
	while (mini->env[i])
	{
		aux[i] = ft_strdup(mini->env[i]);
		i++;
	}
	clean_env(mini->env);
	mini->env = aux;
	mini->env[i] = join_key_value(key, value);
}

/* Realiza uma busca na env pela key paramentro
e retorna o indice. */
ssize_t	search_envp(char **envp, char *key)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (!key || !envp)
		return (-1);
	while (envp[i])
	{
		len = keylen(envp[i]);
		if ((keylen(key) == (size_t)len) && (ft_strncmp(envp[i], key, len) == 0))
			return (i);
		i++;
	}
	return (-1);
}

/* Edita uma variavel que já exista em env */
int	edit_envp(t_sys_config *mini, char *key, char *new_value)
{
	int	i;

	if (!mini->env || !key)
		return (0);
	i = search_envp(mini->env, key);
	if (i < 0)
		return (0);
	free(mini->env[i]);
	mini->env[i] = join_key_value(key, new_value);
	return (1);
}

/* Pega todas as variaveis de ambiente e alloca
na struct.*/
void	get_envp(char **envp, t_sys_config *data)
{
	int	i;

	i = 0;
	data->env = (char **)ft_calloc(sizeof(char *), amount_vars(envp) + 1);
	while (envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
}
