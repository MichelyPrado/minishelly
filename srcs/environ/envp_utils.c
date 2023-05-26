/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:14:22 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 18:32:22 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	keylen(char *var_env)
{
	char	*p;

	p = NULL;
	p = ft_strchr(var_env, '=');
	if (!p)
		return (ft_strlen(var_env));
	return (p - var_env);
}

char	**alloc_env(char **env, int slots)
{
	int		amount;
	char	**new_env;

	amount = ft_listlen(env);
	new_env = (char **) ft_calloc(sizeof(char *), amount + slots);
	if (!new_env)
		return (NULL);
	return (new_env);
}

int	env_empty(char ***env, char *key, char *value)
{
	if (!(*env))
	{
		(*env) = (char **) ft_calloc(sizeof(char *), 2);
		(*env)[0] = ft_strjoin(key, value);
		return (1);
	}
	return (0);
}
