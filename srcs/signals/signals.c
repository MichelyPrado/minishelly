/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:26:30 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/24 17:55:42 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler( int sig)
{
	printf("CAPTUROU O SINAL: %i\n", sig);
	if (sig == SIGINT && *get_is_fork() == 0)
	{
		g_fd = 0;
		printf("calma pora: %i\n", g_fd);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();		
	}
	else
	{
		write(1, "\n", 1);
	}
}

void	wait_signal()
{
	signal(SIGINT, NULL);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
