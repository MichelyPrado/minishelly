/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:07 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/18 20:15:35 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sys_config	*start_sys(char **environ)
{
	t_sys_config	*mini;

	mini = (t_sys_config *) malloc(sizeof(t_sys_config));
	get_envp(environ, mini);
	mini->prompt = malloc(sizeof(char **) * 3);
	mini->prompt[0] = create_prompt(6, L_GREEN, SHELLNAME, \
									L_BLUE, " dapaulin", L_WHITE, PROP);
	mini->prompt[1] = create_prompt(4, L_GREEN, PROPQUOTE, L_WHITE, PROP);
	mini->prompt[2] = NULL;
	mini->new_parser = NULL;
	mini->tokens = &((t_token){0});
	mini->nlen_parser = 0;
	mini->path = (char **){NULL};
	mini->str = NULL;
	return (mini);
}

void	clean_sys(t_sys_config *mini)
{
	clean_strlist(&(mini->env));
	clean_strlist(&(mini->prompt));
	if (mini)
		free(mini);
}

void	clean_strlist(char ***strs)
{
	int	i;

	i = 0;
	if (!(*strs))
		return ;
	while((*strs)[i])
		free((*strs)[i++]);
	if (*strs)
		free(*strs);
	*strs = NULL;
}
