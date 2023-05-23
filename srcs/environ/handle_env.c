/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:21:28 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/21 18:26:01 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	clean_strlist(&mini->env);
	mini->env = aux;
}

/* Cria uma nova variavel em env se não existir ou
edita caso exista. */
void	ft_export(char ***env, char *key, char *value)
{
	int		i;
	char	**aux;

	if (!key)
		return ;
	if (env_empty(env, key, value))
		return ;
	if (edit_envp(env, key, value))
		return ;
	aux = alloc_env(*env, MORE_ONE_SPACE);
	i = 0;
	while ((*env)[i])
	{
		aux[i] = ft_strdup((*env)[i]);
		i++;
	}
	clean_strlist(&(*env));
	*env = aux;
	(*env)[i] = ft_strjoin(key, value);
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
		if ((keylen(key) == (size_t)len)
			&& (ft_strncmp(envp[i], key, len) == 0))
			return (i);
		i++;
	}
	return (-1);
}

/* Edita uma variavel que já exista em env */
int	edit_envp(char ***env, char *key, char *new_value)
{
	int	i;

	if (!(*env) || !key)
		return (0);
	i = search_envp((*env), key);
	if (i < 0)
		return (0);
	free((*env)[i]);
	(*env)[i] = ft_strjoin(key, new_value);
	return (1);
}

/* Pega todas as variaveis de ambiente e alloca
na struct.*/
void	get_envp(char **envp, t_sys_config *data)
{
	int	i;

	i = 0;
	data->env = (char **)ft_calloc(sizeof(char *), ft_listlen(envp) + 1);
	while (envp && envp[i])
	{
		data->env[i] = ft_strdup(envp[i]);
		i++;
	}
}
