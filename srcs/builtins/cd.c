/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:20:35 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 14:57:17 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	update_pwd(char ***pwd, ssize_t pwd_index, char *key, char **value)
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

int	too_much_args(char **token)
{
	if (ft_listlen(token) > 2)
	{
		ft_print_err(1, "cd: too many arguments. 😿\n");
		return (1);
	}
	return (0);
}

int	special_cases(char ***token, char **env)
{
	if (too_much_args(*token))
		return (1);
	if (!(*token)[1])
	{
		clean_strlist(token);
		*token = ft_calloc(3, sizeof(char *));
		(*token)[0] = ft_strdup("cd");
		(*token)[1] = ft_strdup("$HOME");
		search_for_symbol(&(*token)[1], '$', env);
		if (!ft_strlen((*token)[1]))
		{
			ft_print_err(1, " cd: HOME not set\n");
			return (1);
		}
	}
	return (0);
}

int	ft_cd(t_sys_config *mini)
{
	ssize_t		old_pwd_index;
	ssize_t		pwd_index;
	char		*pwd_value;

	if (special_cases(&mini->tokens->token, mini->env))
		return (0);
	pwd_index = search_envp(mini->env, "PWD");
	old_pwd_index = search_envp(mini->env, "OLDPWD");
	pwd_value = getcwd(NULL, 0);
	if (chdir(mini->tokens->token[1]) != -1)
	{
		update_pwd(&(mini->env), old_pwd_index, "OLDPWD=", &pwd_value);
		pwd_value = getcwd(NULL, 0);
		update_pwd(&(mini->env), pwd_index, "PWD=", &pwd_value);
		return (0);
	}
	else
		ft_print_err(1, " No such file or directory\n");
	if (pwd_value)
		free(pwd_value);
	return (0);
}
