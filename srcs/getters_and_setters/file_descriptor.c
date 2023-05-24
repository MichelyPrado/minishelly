/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:06:59 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/23 18:27:33 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*get_fd_in(void)
{
	static int	fd;

	return (&fd);
}

int	*get_fd_out(void)
{
	static int	fd;

	return (&fd);
}

int	exit_input_error(int status_code)
{
	close(0);
	dup2(*get_fd_bkp_in(), 0);
	set_status_code(status_code);
	return (1);
}

int	exit_output_error(int status_code)
{
	close(1);
	dup2(*get_fd_bkp_out(), 1);
	set_status_code(status_code);
	return (1);
}

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

int	*get_fd_bkp_out(void)
{
	static int	bkp;

	return (&bkp);
}

int	*get_fd_bkp_in(void)
{
	static int	bkp;

	return (&bkp);
}
