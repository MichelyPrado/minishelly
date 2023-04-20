/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:25:16 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 23:06:14 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_paths(char **env, t_sys_config *mini)
{
	while (ft_strcmp("PATH", *env))
		env++;
	mini->path = ft_split((*env + 5), ':');
}

int	ft_is_cmd(char **token, char **path)
{
	int erro = access(token[0], X_OK);
	return (erro);
	token = NULL;
	path = NULL;
}