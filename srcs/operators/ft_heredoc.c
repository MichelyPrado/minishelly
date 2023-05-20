/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/19 20:55:56 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_heredoc(t_sys_config *ms)
{
    char    *read;
    char    *hd_str;

    hd_str = "";
    read = NULL;
    if (ms->exec->flag == BFALSE)
        ms->exec->pid = fork();
    if (ms->exec->pid == 0)
    {
        while(1)
        {
            read = readline("heredoc> ");
            if (!read)
            {
                free(hd_str);
                ft_printf("\nwarning: here-document delimited by end-of-file (wanted '%s')\n", ms->tokens->token[1]);
                return (1);
            }
            if (ft_strncmp(read, ms->tokens->token[1], ft_strlen(ms->tokens->token[1]) + 1))
            {
                hd_str = create_prompt(3, hd_str, read, "\n");
                read = NULL;
                continue ;
            }
            if (ms->tokens->next && (ms->tokens->next->type >= 4 && ms->tokens->next->type <= 8))
                
            ft_printf("%s", hd_str);
            free(hd_str);
            break ;
        }
        exit(0);
    }
    ms->exec->i++;
    return (0);
}