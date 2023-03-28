/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 22:25:24 by msilva-p          #+#    #+#             */
/*   Updated: 2022/12/11 20:36:15 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_number(int nb)
{
	int	digits;

	digits = 0;
	if (nb < 0)
	{
		digits = ft_print_char('-');
		if (nb < -9)
			digits += ft_print_number(-(nb / 10));
		digits += ft_print_char(-(nb % 10) + '0');
	}
	else if (nb > 9)
	{
		digits = ft_print_number(nb / 10);
		digits += ft_print_char((nb % 10) + '0');
	}
	else
		digits = ft_print_char(nb + '0');
	return (digits);
}

int	ft_print_string(char *string)
{
	if (!string)
		return (write(1, "(null)", 6));
	else
		return (write(1, string, ft_strlen(string)));
}

int	ft_print_hexa(unsigned int hexa, char c)
{
	int	digits;

	digits = 0;
	if (hexa > 15)
	{
		digits = ft_print_hexa(hexa / 16, c);
		digits += ft_print_hexa(hexa % 16, c);
	}
	else if (hexa >= 10)
	{
		if (c == 'x')
			digits = ft_print_char(hexa + 87);
		else
			digits = ft_print_char(hexa + 55);
	}
	else
		digits = ft_print_char(hexa + '0');
	return (digits);
}

int	ft_print_unsigned(unsigned int un)
{
	int	digits;

	digits = 0;
	if (un > 9)
	{
		digits = ft_print_unsigned(un / 10);
		digits += ft_print_char((un % 10) + '0');
	}
	else
		digits = ft_print_char(un + '0');
	return (digits);
}

int	ft_print_pointer(unsigned long pointer, char c)
{
	int	digits;

	digits = 0;
	if (c == 'p')
	{
		if (pointer == 0)
			return (write(1, "(nil)", 5));
		digits = write(1, "0x", 2);
		c = 0;
	}
	if (pointer > 15)
	{
		digits += ft_print_pointer(pointer / 16, c);
		digits += ft_print_pointer(pointer % 16, c);
	}
	else if (pointer >= 10)
	{
		digits += ft_print_char(pointer + 87);
	}
	else
		digits += ft_print_char(pointer + '0');
	return (digits);
}
