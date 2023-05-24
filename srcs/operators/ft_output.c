/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:03:37 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 13:27:21 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	fd_output_validation(int *fd, char *token)
{
	if (run_access(token, W_OK))
	{
		*fd = open(token, O_WRONLY | O_TRUNC);
		if (*fd == -1)
			return (ft_exit_in_out_error(1));
	}
	else
	{
		if (*get_status_code() == 126)
		{
			*fd = open(token, O_WRONLY | O_CREAT, 0644);
			if (*fd == -1)
				return (ft_exit_in_out_error(1));
		}
		else
			return (ft_exit_in_out_error(1));
	}
	return (0);
}

int	ft_output(t_sys_config *ms)
{
	int				fd;
	t_process_func	*func;

	func = ms->exec->func;
	if (fd_output_validation(&fd, ms->tokens->token[1]))
		return (1);
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
