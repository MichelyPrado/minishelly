/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:07 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 11:01:48 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_more(t_sys_config *ms);

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

	*get_fd_bkp_out() = dup(1);
	*get_fd_bkp_in() = dup(0);
	mini = (t_sys_config *) malloc(sizeof(t_sys_config));
	if (!mini)
		normal_exit(free, ENOMEM, mini);
	get_envp(environ, mini);
	mini->exec = &((t_exec){0});
	mini->prompt = ft_calloc(sizeof(char **), 3);
	if (!mini->prompt)
	{
		clean_strlist(&mini->prompt);
		normal_exit(free, ENOMEM, mini);
	}
	init_more(mini);
	return (mini);
}

void	update_unbound_vars(char *key, t_sys_config *mini)
{
	if (!ft_strcmp(key, "USER"))
	{
		if (mini->prompt[0])
			free(mini->prompt[0]);
		mini->prompt[0] = create_prompt(6, L_GREEN, SHELLYNAME, L_BLUE, \
		cat_user(mini->env), L_WHITE, PROP);
	}
	else if (!ft_strcmp(key, "PATH"))
	{
		clean_strlist(&mini->path);
		mini->path = split_paths(mini->env);
	}
}

static void	init_more(t_sys_config *ms)
{
	ms->prompt[0] = create_prompt(6, L_GREEN, SHELLYNAME, L_BLUE, \
										cat_user(ms->env), L_WHITE, PROP);
	ms->prompt[1] = create_prompt(4, L_GREEN, PROPQUOTE, L_WHITE, PROP);
	ms->prompt[2] = NULL;
	ms->new_parser = NULL;
	ms->head = NULL;
	ms->tokens = &((t_token){0});
	ms->nlen_parser = 0;
	ms->path = split_paths(ms->env);
	ms->str = NULL;
}
