/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:32:25 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/16 04:21:28 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	printf_export(char **token, char **env)
{
	int		i;
	int		size;
	char	*key;

	if (!token[1])
	{
		i = 0;
		while (env[i])
		{
			size = keylen(env[i]);
			key = ft_substr(env[i], 0, size);
			if (env[i][size] == '=')
				ft_printf("declare -x %s=\"%s\"\n", key, &env[i][size + 1]);
			else
				ft_printf("declare -x %s\n", key);
			if (key)
				free(key);
			i++;
		}
		return (1);
	}
	return (0);
}

int	check_existence(char **token, char **key, char **env, int i)
{
	int	loc;
	int	size;

	size = keylen(token[i]);
	*key = ft_substr(token[i], 0, size);
	loc = search_envp(env, *key);
	if (loc >= 0 && !ft_strchr(token[i], '=') && \
	ft_strchr(env[loc], '='))
	{
		if (*key)
			free(*key);
		return (0);
	}
	return (size);
}

int	b_export(t_sys_config *mini)
{
	int		i;
	int		size;
	char	*key;
	char	**token;

	token = mini->tokens->token;
	if (token[0] && printf_export(token, mini->env))
		return (0);
	i = 1;
	while (token[i])
	{
		if (!check_is_a_valid_var(token[i]))
			return (ft_print_err(1, " not a valid identifier"), 1);
		size = check_existence(token, &key, mini->env, i);
		if (!size)
			return (0);
		ft_export(&mini->env, key, &token[i][size]);
		update_unbound_vars(key, mini);
		if (key)
			free(key);
		i++;
	}
	return (0);
}
