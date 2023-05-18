/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/18 06:54:50 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_heredoc(t_sys_config *ms)
{
    char    *read;
    char    *hd_str;

    hd_str = "";
    read = NULL;
    while(1)
    {
        read = readline("heredoc> ");
        if (!ft_strncmp(read, ms->tokens->token[1], ft_strlen(ms->tokens->token[1]) + 1))
        {
            printf("%s\n", hd_str);
            free(hd_str);
            break ;
        }
        hd_str = create_prompt(2, hd_str, read);
        read = NULL;
    }
    return (0);
}