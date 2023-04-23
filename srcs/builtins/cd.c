/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:20:35 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 13:52:59 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_sys_config *mini)
{
	ssize_t		old_pwd;
	ssize_t		pwd;
	char		*pwd_value;

	pwd_value = getcwd(NULL, 0);
	pwd = search_envp(mini->env, "PWD");
	chdir("buitins/");
	old_pwd = search_envp(mini->env, "OLDPWD");
	if (chdir(mini->tokens->token[1]) != -1)
	{
		if (mini->env[old_pwd])
			free(mini->env[old_pwd]);
		if (old_pwd)
			mini->env[old_pwd] = ft_strjoin("OLDPWD=", pwd_value);
		if (mini->env[pwd])
			free(mini->env[pwd]);
		if (pwd_value)
			free(pwd_value);
		pwd_value = getcwd(NULL, 0);
		if (pwd)
			mini->env[pwd] = ft_strjoin("PWD=", pwd_value);
		if (pwd_value)
			free(pwd_value);
		return (0);
	}
	if (pwd_value)
		free(pwd_value);
	return (0);
}
