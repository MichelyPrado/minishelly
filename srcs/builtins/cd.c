/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:20:35 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/09 20:19:45 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void update_pwd(char ***pwd, ssize_t pwd_index, char *key, char **value)
{
	if ((*pwd)[pwd_index])
		free((*pwd)[pwd_index]);
	(*pwd)[pwd_index] = NULL;
	if (pwd_index)
		(*pwd)[pwd_index] = ft_strjoin(key, *value);
	if (*value)
		free(*value);
	*value = NULL;
}

int	ft_listlen(char **token)
{
	int	i;

	i = 0;
	while (token[i])
		i++;
	return (i);
}

int	too_much_args(char **token)
{
	if (ft_listlen(token) > 2)
	{
		ft_printf("cd: too many arguments. 😿");
		return (1);
	}
	return (0);
}

int	special_cases(char ***token, char **env)
{
	if (!(*token)[1])
	{
		clean_strlist(token);
		*token = ft_calloc(3, sizeof(char *));
		(*token)[0] = ft_strdup("cd");
		(*token)[1] = ft_strdup("$HOME");
		expand_symbol(&(*token)[1], '$', env);
	}
	return (0);
}

int	ft_cd(t_sys_config *mini)
{
	ssize_t		old_pwd_index;
	ssize_t		pwd_index;
	char		*pwd_value;
	int			err;

	
	if (too_much_args(mini->tokens->token))
		return (1);
	pwd_value = getcwd(NULL, 0);
	pwd_index = search_envp(mini->env, "PWD");
	old_pwd_index = search_envp(mini->env, "OLDPWD");
	err = special_cases(&mini->tokens->token, mini->env);
	if (err)
		return (err);
	if (chdir(mini->tokens->token[1]) != -1)
	{
		update_pwd(&(mini->env), old_pwd_index, "OLDPWD=", &pwd_value);
		pwd_value = getcwd(NULL, 0);
		update_pwd(&(mini->env), pwd_index, "PWD=", &pwd_value);
		return (0);
	}
	if (pwd_value)
		free(pwd_value);
	return (0);
}
