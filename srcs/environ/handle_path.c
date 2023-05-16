/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:25:16 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/16 15:58:31 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**split_paths(char **env)
{
	int	i;

	if (!env || !*env)
		return (NULL);
	i = search_envp(env, "PATH");
	if (i < 0)
		return (NULL);
	return (ft_split(&env[i][keylen(env[i])], ':'));
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
	i = 0;
	if (!path)
		return (err);
	while (path[i])
	{
		tmp = create_prompt(3, path[i], "/", *token);
		err = access(tmp, F_OK | X_OK);
		if (path_is_valid(err, tmp, token))
			return (0);
		if (tmp)
			free(tmp);
		i++;
	}
	err = access(*token, F_OK | X_OK);
	if (err == 0)
		return (0);
	return (-1);
}
