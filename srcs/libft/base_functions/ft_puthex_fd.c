/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:29:00 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:49:05 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_puthex_fd_aux(unsigned long nb, int fd, int *ret, char *caset)
{
	if (nb >= 16)
		ft_puthex_fd_aux(nb / 16, fd, ret, caset);
	*ret += ft_putchar_fd(caset[(nb % 16)], fd);
}

int	ft_puthex_fd(unsigned long nb, int fd, char *caset)
{
	int	size;

	size = 0;
	ft_puthex_fd_aux(nb, fd, &size, caset);
	return (size);
}
