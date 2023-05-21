/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 12:26:30 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/21 16:32:00 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sig_handler( int sig, siginfo_t *info, void *context)
{
	(void)context;
	if (sig == SIGINT && info->si_pid)
	{
		write(1, "\n", 1);
		rl_on_new_line ();
		rl_replace_line ("", 0);
		rl_redisplay ();
	}
}

void	wait_signal(t_sa *sa)
{
	sa->sa_sigaction = sig_handler;
	sigaction(SIGINT, sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_a(int sig)
{
	const char	*signal_mini;

	signal_mini = 0;
	if (sig == SIGINT)
		signal_mini = "SIGINT";
	else if (sig == SIGQUIT)
		signal_mini = "SIGQUIT";
}
