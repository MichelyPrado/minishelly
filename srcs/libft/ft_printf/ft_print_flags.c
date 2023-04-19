/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:36:21 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:35:58 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	printf_formatchar(int fd, t_typechar *format)
{
	int	bsr;

	bsr = 0;
	format->bytes--;
	if (!format->minus)
		bsr += print_spaces(fd, &format->bytes, ' ');
	bsr += ft_putchar_fd(format->value, fd);
	bsr += print_spaces(fd, &format->bytes, ' ');
	return (bsr);
}

int	printf_formatstring(int fd, t_typestring *format)
{
	int	bsr;
	int	size;

	bsr = 0;
	size = ft_strlen(format->value);
	if ((!format->bytes_s && !format->dot) || size <= format->bytes_s)
		format->bytes -= size;
	else
	{
		format->bytes -= format->bytes_s;
		size = format->bytes_s;
	}
	if (!format->minus)
	{
		bsr += print_spaces(fd, &format->bytes, ' ');
	}
	bsr += write(fd, format->value, size);
	bsr += print_spaces(fd, &format->bytes, ' ');
	if (format->value)
		free(format->value);
	return (bsr);
}

int	printf_formatint(int fd, t_typeint *format)
{
	int		bsr;
	int		size;
	char	*str_num;

	bsr = 0;
	str_num = ft_itoa_base(format->value, BASED);
	if (format->dot && !format->bytes_s && !format->value)
		size = 0;
	else
		size = ft_strlen(str_num);
	format_iflags(&format, size);
	if (!format->minus)
		bsr += print_spaces(fd, &format->bytes, ' ');
	if (format->plus || format->signal == '-')
		bsr += write(fd, &format->signal, 1);
	else if (format->space)
		bsr += ft_putchar_fd(' ', fd);
	bsr += print_spaces(fd, &format->bytes_s, '0');
	bsr += write(fd, str_num, size);
	bsr += print_spaces(fd, &format->bytes, ' ');
	if (str_num)
		free(str_num);
	return (bsr);
}

int	printf_formathex(int fd, t_typehex *format)
{
	int		bsr;
	int		size;
	char	*str_num;

	bsr = 0;
	str_num = ft_itoa_base(format->value, BASEH);
	if (format->dot && !format->bytes_s && !format->value)
		size = 0;
	else if (format->caset == 'X')
		size = ft_strlen_upper(str_num);
	else
		size = ft_strlen(str_num);
	format_xflags(&format, size);
	if (!format->minus)
		bsr += print_spaces(fd, &format->bytes, ' ');
	if (format->hash && format->value)
		bsr += ft_putchar_fd('0', fd) + ft_putchar_fd(format->caset, fd);
	bsr += print_spaces(fd, &format->bytes_s, '0');
	bsr += write(fd, str_num, size);
	bsr += print_spaces(fd, &format->bytes, ' ');
	if (str_num)
		free(str_num);
	return (bsr);
}
