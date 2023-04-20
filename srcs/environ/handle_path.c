/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:25:16 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/20 01:17:51 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_paths(char **env, t_sys_config *mini)
{
	while (ft_strcmp("PATH", *env))
		env++;
	mini->path = ft_split((*env + 5), ':');
}

static int	path_is_valid(int err, char *tmp, char **token)
{
	if (err == 0)
	{
		if (*token)
			free(*token);
		*token = tmp;
		return (1);
	}
	return (0);
}

int	cmd_path_valid(char **token, char **path)
{
	int		i;
	int		err;
	char	*tmp;
	
	tmp = NULL;
	err = -1;
	if (!token || !*token)
		return (err);
	err = access(*token, X_OK);
	if (err == 0)
		return (0);
	i = 0;
	if (!path)
		return (err);
	while (path[i])
	{
		tmp = create_prompt(3, path[i], "/", *token);
		err = access(tmp, X_OK);
		if (path_is_valid(err, tmp, token))
			return (0);
		if (tmp)
			free(tmp);
		i++;
	}
	return (err);
}