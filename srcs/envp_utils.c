/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:14:22 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/20 19:44:32 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_vars(char **envp)
{
	int	len;

	len = 0;
	while (*envp != NULL && envp[len])
		len++;
	return (len);
}

size_t	keylen(char *var_env)
{
	char	*p;

	p = NULL;
	p = ft_strchr(var_env, '=');
	if (!p)
		return (0);
	return (p - var_env);
}

void	clean_env(char **new_envp)
{
	int	i;

	i = 0;
	while (new_envp[i])
	{
		if (new_envp[i])
			free(new_envp[i]);
		i++;
	}
	if (new_envp)
		free(new_envp);
}

char	**alloc_envp(t_minishelly *mini, int space)
{
	char	**aux;
	size_t	amount;
	
	amount = count_vars(mini->e);
	aux = (char **) ft_calloc(sizeof(char *), amount + space);
	if (!aux)
		return (NULL);
	return (aux);
}
