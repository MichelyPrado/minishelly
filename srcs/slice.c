/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:20:16 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/20 19:48:59 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	mini->e[i] = ft_strjoin(key, value);
}
