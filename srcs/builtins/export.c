/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 21:32:25 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:53:10 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	b_export(t_sys_config *mini)
{
	int		i;
	int		j;
	int		size;
	char	*key;
	
	if (!mini->tokens->token[1])
	{
		i = 0;
		while (mini->env[i])
		{
			size = keylen(mini->env[i]);
			key = ft_substr(mini->env[i], 0, size);
			if (mini->env[i][size] == '=')
				ft_printf("declare -x %s=\"%s\"\n", key, &mini->env[i][size + 1]);
			else 
				ft_printf("declare -x %s\n", key);
			if (key)
				free(key);
			i++;
		}
		return (0);
	}

	j = 1;
	while (mini->tokens->token[j])
	{
		size = keylen(mini->tokens->token[j]);
		key = ft_substr(mini->tokens->token[j], 0, size);
		int loc = search_envp(mini->env, key);
		if (loc >= 0 && !ft_strchr(mini->tokens->token[j], '=') && \
		ft_strchr(mini->env[loc], '='))
		{
			if (key)
				free(key);	
			return (0);
		}
		ft_export(&mini->env, key, &mini->tokens->token[j][size]);
		if (key)
			free(key);
		j++;
	}

	return (0);
}
