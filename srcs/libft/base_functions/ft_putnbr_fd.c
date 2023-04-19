/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:21:12 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:49:08 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_putnbr_fd_aux(unsigned int nb, int fd, int *ret)
{
	char			c;

	if (nb >= 10)
		ft_putnbr_fd_aux(nb / 10, fd, ret);
	c = (nb % 10) + 48;
	*ret += ft_putchar_fd(c, fd);
}

int	ft_putnbr_fd(int nb, int fd)
{
	int				size;
	int				signal;

	size = 0;
	signal = 1;
	if (nb < 0)
	{
		ft_putchar_fd('-', fd);
		signal = -1;
	}
	ft_putnbr_fd_aux(nb * signal, fd, &size);
	return (size);
}
