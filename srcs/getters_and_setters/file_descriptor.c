/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_descriptor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 22:06:59 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/20 22:31:07 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*get_fd(void)
{
	static int	fd;

	return (&fd);
}

int	*get_fd_bkp(void)
{
	static int	bkp;

	return (&bkp);
}
