/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:26:30 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/09 19:01:41 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//função sigaction / na função de init inicializar ela
//sigaction = passar o sinal e a função correspondente

//int sigaction(int signum, const struct sigaction *restrict act, struct sigaction *restrict oldact);

void sig_handler(int sig)
{
	(void)sig;

    //if (sig == SIGINT && info->si_pid)
	{
		write(1, "\n", 1);
		rl_replace_line ("", 0);
		rl_on_new_line ();
		rl_redisplay ();
		
	}
}

void    wait_signal(t_sa *sa)
{
	sa->sa_sigaction = sig_handler;
	sigaction(SIGINT, sa, NULL); 
	signal(SIGQUIT, SIG_IGN);     
}

// void sig_a(int sig) 
// {
//     const char *signal_mini;

//     if (sig == SIGINT) {
//         signal_mini = "SIGINT";
//     } else if (sig == SIGQUIT) {
//         signal_mini = "SIGQUIT";
//     } 
// }