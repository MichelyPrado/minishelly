/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 22:28:29 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 22:29:59 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	signal_break_heredoc(int signal)
{
	t_sys_config	*ms;

	ms = *get_ms();
	if (signal == SIGINT)
	{
		clean_for_exec(ms);
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_replace_line("", 0);
		exit(0);
	}
}

void	wait_signal_heredoc(void)
{
	signal(SIGINT, &signal_break_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
