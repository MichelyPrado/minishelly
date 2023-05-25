/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:26:30 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/25 19:05:38 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler( int sig)
{
	if (sig == SIGINT && *get_is_fork() == 0)
	{
		g_fd = 0;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

void    signal_break_heredoc(int signal)
{
    (void)signal;
    ft_putchar_fd('\n', STDOUT_FILENO);
    exit(130);
}

void	wait_signal(void)
{
	signal(SIGINT, NULL);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
