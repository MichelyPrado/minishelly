/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:06:59 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 20:34:04 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*get_fd(void)
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
