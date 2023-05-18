/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/18 19:55:50 by msilva-p         ###   ########.fr       */
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
        if (!read)
        {
            free(hd_str);
            printf("\nwarning: here-document delimited by end-of-file (wanted '%s')\n", ms->tokens->token[1]);
            return (1);
        }
        if (ft_strncmp(read, ms->tokens->token[1], ft_strlen(ms->tokens->token[1]) + 1))
        {
            hd_str = create_prompt(3, hd_str, read, "\n");
            read = NULL;
            continue ;
        }
        printf("%s", hd_str);
        free(hd_str);
        break ;
    }
    return (0);
}