/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:07:10 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 19:41:54 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	dup_fd_out(int fd)
{
	int		oldfd;
	char	*term_name;

	oldfd = *get_fd_out();
	term_name = ttyname(oldfd);
	if (term_name != NULL)
		close(1);
	else
		free(term_name);
	*get_fd_out() = fd;
	return (dup2(fd, 1));
}

int	dup_fd_in(int fd)
{
	int		oldfd;
	char	*term_name;

	oldfd = *get_fd_in();
	term_name = ttyname(oldfd);
	if (term_name != NULL)
		close(0);
	else
		free(term_name);
	*get_fd_in() = fd;
	return (dup2(fd, 0));
}

int	ft_exit_in_out_error(int status_code)
{
	close(1);
	close(0);
	dup2(*get_fd_bkp_out(), 1);
	dup2(*get_fd_bkp_in(), 0);
	set_status_code(status_code);
	return (1);
}
