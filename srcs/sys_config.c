/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 16:44:07 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/17 15:43:31 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_sys_config *start_sys()
{
    t_sys_config *mini;
    extern char **environ;

    mini = malloc(sizeof(t_sys_config));
    get_envp(environ, mini);
    mini->prompt = malloc(sizeof(char **) * 3);
    mini->prompt[0] = create_prompt(6, L_GREEN, SHELLNAME, \
                                    L_BLUE, " dapaulin", L_WHITE, PROP);
    mini->prompt[1] = create_prompt(4, L_GREEN, PROPQUOTE, L_WHITE, PROP);
    mini->prompt[2] = NULL;
    mini->new_parser = NULL;
    mini->tokens = NULL;
    mini->nlen_parser = 0;
    mini->path = NULL;
    mini->str = NULL;
    return (mini);
}