/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:20:35 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/09 12:27:43 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void update_pwd(char ***pwd, ssize_t pwd_pos, char *key, char **value)
{
	if ((*pwd)[pwd_pos])
		free((*pwd)[pwd_pos]);
	(*pwd)[pwd_pos] = NULL;
	if (pwd_pos)
		(*pwd)[pwd_pos] = ft_strjoin(key, *value);
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
		ft_printf("cd: too many arguments ⚠️");
		return (1);
	}
	return (0);
}

int	ft_cd(t_sys_config *mini)
{
	ssize_t		old_pwd;
	ssize_t		pwd;
	char		*pwd_value;

	if (too_much_args(mini->tokens->token))
		return (1);
	pwd_value = getcwd(NULL, 0);
	pwd = search_envp(mini->env, "PWD");
	old_pwd = search_envp(mini->env, "OLDPWD");
	if (!mini->tokens->token[1])
	{
		clean_strlist(&mini->tokens->token);
		mini->tokens->token = ft_calloc(3, sizeof(char *));
		mini->tokens->token[0] = ft_strdup("cd");
		mini->tokens->token[1] = ft_strdup("$HOME");
		expand_symbol(&mini->tokens->token[1], '$', mini->env); 
	}
	if (chdir(mini->tokens->token[1]) != -1)
	{
		update_pwd(&(mini->env), old_pwd, "OLDPWD=", &pwd_value);
		pwd_value = getcwd(NULL, 0);
		update_pwd(&(mini->env), pwd, "PWD=", &pwd_value);
		return (0);
	}
	if (pwd_value)
		free(pwd_value);
	return (0);
}
