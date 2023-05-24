/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 13:45:46 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 10:28:42 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_input(t_sys_config *ms)
{
	int				fd;
	t_process_func	*func;

	func = ms->exec->func;
	if (access(ms->tokens->token[1], F_OK) == -1)
		return (ft_exit_in_out_error(1));
	fd = open(ms->tokens->token[1], O_RDONLY);
	if (fd == -1)
		return (ft_exit_in_out_error(ENOENT));
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		if (dup_fd_in(fd) == -1)
			sys_exit_err(clean_data, ms, NULL);
		close(fd);
		if (func[ms->tokens->type](ms))
			return (1);
		close(0);
		if (dup2(*get_fd_bkp_in(), 0) == -1)
			sys_exit(clean_data, EBADF, ms);
	}
	set_status_code(0);
	return (0);
}
