/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:14:22 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/18 16:13:36 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_envp_items(char **envp)
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

char	*join_key_value(char *key, char *value)
{
	char	*dst;
	int		len;

	len = (ft_strlen(key) + ft_strlen(value) + 2);
	dst = ft_calloc(sizeof(char), len);
	ft_strlcat(dst, key, len);
	ft_strlcat(dst, "=", len);
	if (value)
		ft_strlcat(dst, value, len);
	else
		ft_strlcat(dst, "", len);
	return (dst);
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
