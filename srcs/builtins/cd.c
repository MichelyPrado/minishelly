/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 19:20:35 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/17 20:32:55 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_cd(t_sys_config *mini)
{
	//ssize_t		old_pwd;
	//ssize_t		pwd;
	int j = 1;
	//char		*pwd_value;

	//pwd_value = NULL;
	//pwd = search_envp(mini->env, "PWD");
	while (mini->tokens->token[j])
	{
		printf("%s\n", mini->tokens->token[j++]);
	}
	chdir("buitins/");
	//old_pwd = search_envp(mini->env, "OLDPWD");
	//if (chdir(mini->tokens->token[1]) != -1)
	//{
		//if (mini->env[old_pwd])
		//	free(mini->env[old_pwd]);
		//mini->env[old_pwd] = ft_strjoin("OLDPWD=", &mini->env[pwd][4]);
		//if (mini->env[pwd])
		//	free(mini->env[pwd]);
		//pwd_value = getcwd(NULL, 0);
		//mini->env[pwd] = ft_strjoin("PWD=", pwd_value);
		//if (pwd_value)
		//	free(pwd_value);
		//return (0);
	//}
	return (0);
}