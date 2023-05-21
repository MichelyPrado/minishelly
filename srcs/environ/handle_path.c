/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 09:25:16 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/21 18:03:59 by dapaulin         ###   ########.fr       */
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

int	run_access(char *path, int flag)
{
	int	err;

	err = access(path, F_OK);
	if (err == 0)
	{
		err = access(path, flag);
		if (err == 0)
		{
			set_status_code(0);
			return (1);
		}
		set_status_code(127);
		return (0);
	}
	set_status_code(126);
	return (0);
}

int	cmd_path_valid(char **token, char **path)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (!token || !*token)
	{
		set_status_code(126);
		return (0);
	}
	while (path && path[i])
	{
		tmp = create_prompt(3, path[i], "/", *token);
		if (run_access(tmp, X_OK))
		{
			if (*token)
				free(*token);
			*token = tmp;
			return (1);
		}
		if (tmp)
			free(tmp);
		i++;
	}
	if (run_access(*token, X_OK))
		return (1);
	else if (*get_status_code() == 127)
		return (-1);
	return (0);
}
