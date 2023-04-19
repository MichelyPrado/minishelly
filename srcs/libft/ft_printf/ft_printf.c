/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:36:22 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:36:16 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_istype(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == '%' || c == 'X')
		return (1);
	else if (c == 'd' || c == 'i' || c == 'u' || c == 'x')
		return (1);
	return (0);
}

int	findflag(char *str)
{
	int	i;

	i = 0;
	while (!ft_istype(str[i]))
		i++;
	return (i);
}

int	select_type(va_list *args, t_format **shape, int fd)
{
	int	bsr;

	bsr = 0;
	if ((*shape)->type == 'c')
		bsr = printchar(fd, va_arg(*args, int), shape);
	else if ((*shape)->type == 's')
		bsr = printstring(fd, va_arg(*args, char *), shape);
	else if ((*shape)->type == 'i' || (*shape)->type == 'd')
		bsr = printint(fd, va_arg(*args, int), shape);
	else if ((*shape)->type == 'u')
		bsr = printint(fd, va_arg(*args, int), shape);
	else if ((*shape)->type == 'x' || (*shape)->type == 'X')
		bsr = printhex(fd, va_arg(*args, unsigned int), shape);
	else if ((*shape)->type == 'p')
		bsr = printhex(fd, va_arg(*args, unsigned long), shape);
	else if ((*shape)->type == '%')
		bsr = printchar(fd, '%', shape);
	if ((*shape)->arg)
		free((*shape)->arg);
	(*shape)->arg = NULL;
	if ((*shape)->flags)
		free((*shape)->flags);
	(*shape)->flags = NULL;
	return (bsr);
}

int	find_next(char *percent, char **s, va_list *args, t_format **shape)
{
	int	num_bytes;

	num_bytes = 0;
	while (percent)
	{
		num_bytes += write(1, (*s), (percent - (*s)));
		(*s) += (percent - (*s)) + 1;
		(*shape)->f_pos = findflag((*s));
		(*shape)->type = (*s)[(*shape)->f_pos];
		(*shape)->flags = ft_strndup((*s), (*shape)->f_pos);
		num_bytes += select_type(args, shape, 1);
		(*s) += (*shape)->f_pos + 1;
		percent = ft_strchr((*s), '%');
	}
	return (num_bytes);
}

int	ft_printf(const char *str, ...)
{
	t_format	*shape;
	va_list		args;
	char		*c_str;
	int			num_bytes;

	num_bytes = 0;
	c_str = (char *)str;
	shape = new_format();
	if (!str)
		return (free(shape), -1);
	va_start(args, str);
	num_bytes += find_next(ft_strchr(str, '%'), &c_str, &args, &shape);
	if (shape)
		free(shape);
	va_end(args);
	return (num_bytes + ft_putstr_fd(c_str, 1));
}
