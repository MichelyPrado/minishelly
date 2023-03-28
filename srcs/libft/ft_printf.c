/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 19:51:01 by msilva-p          #+#    #+#             */
/*   Updated: 2022/12/11 20:43:14 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_char(int b)
{
	return (write(1, &b, 1));
}

static int	ft_conditions(char character, va_list args)
{
	if (character == 'd' || character == 'i')
		return (ft_print_number(va_arg(args, int)));
	else if (character == 's')
		return (ft_print_string(va_arg(args, char *)));
	else if (character == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (character == 'x' || character == 'X' )
		return (ft_print_hexa(va_arg(args, unsigned int), character));
	else if (character == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (character == 'p')
		return (ft_print_pointer(va_arg(args, unsigned long), 'p'));
	else
		return (ft_print_char(character));
}

int	ft_printf(const char *string, ...)
{
	va_list	args;
	int		lenght;

	lenght = 0;
	va_start(args, string);
	while (*string != '\0')
	{
		if (*string == '%')
		{
			string++;
			lenght += ft_conditions(*string, args);
		}
		else
			lenght += write(1, string, 1);
		string++;
	}
	va_end(args);
	return (lenght);
}
