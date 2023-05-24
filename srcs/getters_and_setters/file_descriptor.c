/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:06:59 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 16:08:04 by dapaulin         ###   ########.fr       */
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
