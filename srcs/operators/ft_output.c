/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:03:37 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/14 12:31:33 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_output(t_sys_config *ms)
{
	int				fd;
	int				bkp;
	t_process_func	*func;

	bkp = dup(1);
	if (bkp == -1)
		sys_exit(clean_data, EBADF, ms);
	func = ms->exec->func;
	fd = open(ms->tokens->token[1], O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		sys_exit(clean_data, ENOENT, ms);
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		if (dup2(fd, 1) == -1)
			sys_exit(clean_data, EBADF, ms);
		close(fd);
		func[ms->tokens->type](ms);
		close(1);
		if (dup2(bkp, 1) ==  -1)
			sys_exit(clean_data, EBADF, ms);
	}
	return (0);
}
