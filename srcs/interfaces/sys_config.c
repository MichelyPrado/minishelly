/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:07 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/11 20:45:08 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cat_user(char **env)
{
	int	i;

	i = search_envp(env, "USER");
	if (i < 0)
		return (NULL);
	return (&env[i][keylen(env[i]) + 1]);
}

t_sys_config	*start_sys(char **environ)
{
	t_sys_config	*mini;

	mini = (t_sys_config *) malloc(sizeof(t_sys_config));
	if (!mini)
		normal_exit(free, ENOMEM, mini);
	get_envp(environ, mini);
	mini->exit_status = 0;
	mini->exec = &((t_exec){0});
	mini->prompt = malloc(sizeof(char **) * 3);
	mini->prompt[0] = create_prompt(6, L_GREEN, SHELLNAME, \
									L_BLUE, cat_user(mini->env), L_WHITE, PROP);
	mini->prompt[1] = create_prompt(4, L_GREEN, PROPQUOTE, L_WHITE, PROP);
	mini->prompt[2] = NULL;
	mini->new_parser = NULL;
	mini->tokens = &((t_token){0});
	mini->nlen_parser = 0;
	mini->path = split_paths(mini->env);
	mini->str = NULL;
	return (mini);
}

void	clean_sys(t_sys_config *mini)
{
	if (mini->new_parser)
		free(mini->new_parser);
	if (mini->str)
		free(mini->str);
	if (mini->exec)
		free(mini->exec);
	clean_strlist(&(mini->env));
	clean_strlist(&(mini->prompt));
	ft_token_free(&(mini->tokens));
	clean_strlist(&(mini->path));
	if (mini)
		free(mini);
}

void	update_unbound_vars(char *key, t_sys_config *mini)
{
	if (!ft_strcmp(key, "USER"))
	{
		if (mini->prompt[0])
			free(mini->prompt[0]);
		mini->prompt[0] = create_prompt(6, L_GREEN, SHELLNAME, L_BLUE, \
		cat_user(mini->env), L_WHITE, PROP);	
	}
	else if (!ft_strcmp(key, "PATH"))
	{
		clean_strlist(&mini->path);
		mini->path = split_paths(mini->env);
	}
}

void	clean_strlist(char ***strs)
{
	int	i;

	i = 0;
	if (!(*strs))
		return ;
	if (*strs)
	{
		while ((*strs)[i])
			free((*strs)[i++]);
		free(*strs);
	}
	*strs = NULL;
}
