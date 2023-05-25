/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:26:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 13:13:53 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	close_files_fds()
{
	close(*get_fd_in());
	close(*get_fd_out());
}

void	close_bkp_terms_fds()
{
	close(*get_fd_bkp_in());
	close(*get_fd_bkp_out());
}

void	close_terms_fds()
{
	close_bkp_terms_fds();
	close(0);
	close(1);
}

void	close_pipes_fds(t_sys_config *mini)
{
	int	i;

	i = 0;
	while (mini->exec && mini->exec->fd && i < *get_num_pipes())
	{
		close(mini->exec->fd[i][0]);
		close(mini->exec->fd[i][1]);
		i++;
	}
}