/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:25:16 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/17 16:10:50 by dapaulin         ###   ########.fr       */
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

int	is_directory(char *path)
{
	struct stat	sb;

	if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (1);
	return (0);
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
		err = access(tmp, F_OK);
		if (err == 0)
		{
			err = access(tmp, X_OK);
			if (path_is_valid(err, tmp, token))
				return (1);
			else
				set_status_code(127);
		}
		else
			set_status_code(126);
		if (tmp)
			free(tmp);
		i++;
	}
	err = access(*token, F_OK);
	if (err == 0)
	{
		err = access(*token, X_OK);
		if (err == 0)
			return (1);
		else {
			set_status_code(127);
			return (-1);
		}
	}
	set_status_code(126);
	return (0);
}
