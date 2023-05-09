/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:44:11 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/09 13:04:56 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void sig_handler( int sig, siginfo_t *info, void *context)
{
	(void)context;
	
    if (sig == SIGINT && info->si_pid)
	{
		rl_on_new_line ();
		rl_replace_line ("", 0);
		rl_redisplay ();
		
	}
}

int	main(int argc, char **argv)
{
	extern char	**environ;
	struct sigaction	t_sa;
	ft_bzero(&t_sa, sizeof(t_sa));
	t_sa.sa_sigaction = sig_handler;
	sigaction(SIGINT, &t_sa, NULL); 
	signal(SIGQUIT, SIG_IGN); 

	return (minishelly(argc, argv, environ));
}
