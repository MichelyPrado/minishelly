/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:00:04 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 10:28:00 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_append(t_sys_config *ms)
{
	int				fd;
	t_process_func	*func;

	func = ms->exec->func;
	if (!run_access(ms->tokens->token[1], W_OK))
	{
		if (*get_status_code() == 126)
		{
			fd = open(ms->tokens->token[1], O_WRONLY \
			| O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (ft_exit_in_out_error(1));
		}
		else
			return (ft_exit_in_out_error(1));
	}
	else
	{
		fd = open(ms->tokens->token[1], O_WRONLY | O_APPEND);
		if (fd == -1)
			return (ft_exit_in_out_error(1));
	}
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		if (dup_fd_out(fd) == -1)
			sys_exit(clean_data, EBADF, ms);
		close(fd);
		if (func[ms->tokens->type](ms))
			return (1);
		close(1);
		if (dup2(*get_fd_bkp_out(), 1) == -1)
			sys_exit(clean_data, EBADF, ms);
	}
	return (0);
}
