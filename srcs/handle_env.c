/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:21:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/20 21:43:21 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Exclui a variavel informada caso ela
exista em env. */
void	ft_unset(t_minishelly *mini, char *key)
{
	int		i;
	int		j;
	char	**aux;

	i = 0;
	j = 0;
	if (!key || !mini->e)
		return ;
	if (search_envp(mini->e, key) < 0)
		return ;
	aux = alloc_env(mini->e, CHAR_NULL);
	while (mini->e[i + j])
	{
		if (ft_strncmp(mini->e[i + j], key, keylen(mini->e[i])) == 0)
			j = 1;
		if (!mini->e[i + j])
			break ;
		aux[i] = ft_strdup(mini->e[i + j]);
		i++;
	}
	clean_env(mini->e);
	mini->e = aux;
}

/* Cria uma nova variavel em env se não existir ou
edita caso exista. */
void	ft_export(t_minishelly *mini, char *key, char *value)
{
	int		i;
	char	**aux;

	if (!key)
		return ;
	if (env_empty(mini, key, value))
		return ;
	if (edit_envp(mini, key, value))
		return ;
	aux = alloc_env(mini->e, MORE_ONE_SPACE);
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

/* Realiza uma busca na env pela key paramentro
e retorna o indice. */
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

/* Edita uma variavel que já exista em env */
int	edit_envp(t_minishelly *mini, char *key, char *new_value)
{
	int	i;

	if (!mini->e || !key)
		return (0);
	i = search_envp(mini->e, key);
	if (i < 0)
		return (0);
	free(mini->e[i]);
	mini->e[i] = join_key_value(key, new_value);
	return (1);
}

/* Pega todas as variaveis de ambiente e alloca
na struct.*/
void	get_envp(char **envp, t_minishelly *data)
{
	int	i;

	i = 0;
	data->e = (char **)ft_calloc(sizeof(char *), amount_vars(envp) + 1);
	while (envp[i])
	{
		data->e[i] = ft_strdup(envp[i]);
		i++;
	}
}
