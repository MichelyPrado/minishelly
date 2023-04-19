/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:25:16 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:49:20 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_paths(char **env, t_sys_config *data)
{
	while (ft_strncmp("PATH", *env, 4))
		env++;
	data->path = ft_split((*env + 5), ':');
}
