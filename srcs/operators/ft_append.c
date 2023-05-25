/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:00:04 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 21:56:15 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fd_append_validation(int *fd, char *token)
{
	if (!run_access(token, W_OK))
	{
		if (*get_status_code() == 126)
		{
			*fd = open(token, O_WRONLY \
			| O_CREAT | O_APPEND, 0644);
			if (*fd == -1)
				return (ft_exit_in_out_error(1));
		}
		else
			return (ft_exit_in_out_error(1));
	}
	else
	{
		*fd = open(token, O_WRONLY | O_APPEND);
		if (*fd == -1)
			return (ft_exit_in_out_error(1));
	}
	return (0);
}

int	ft_append(t_sys_config *ms)
{
	int				fd;
	t_process_func	*func;

	func = ms->exec->func;
	if (fd_append_validation(&fd, ms->tokens->token[1]))
		return (1);
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		if (dup_fd_out(fd) == -1)
			sys_exit(clean_for_exec, EBADF, ms);
		close(fd);
		if (func[ms->tokens->type](ms))
			return (1);
		close(1);
		if (dup2(*get_fd_bkp_out(), 1) == -1)
			sys_exit(clean_for_exec, EBADF, ms);
	}
	return (0);
}
