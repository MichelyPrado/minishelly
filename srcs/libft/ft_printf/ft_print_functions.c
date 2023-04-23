/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_functions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:36:21 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:36:01 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	printchar(int fd, char c, t_format **shape)
{
	(*shape)->arg = formatchar(c, (*shape)->flags);
	if (!(*shape)->arg)
		return (0);
	return (printf_formatchar(fd, (*shape)->arg));
}

int	printstring(int fd, char *str, t_format **shape)
{
	(*shape)->arg = formatstring(str, (*shape)->flags);
	if (!(*shape)->arg)
		return (0);
	return (printf_formatstring(fd, (*shape)->arg));
}

int	printint(int fd, int integer, t_format **shape)
{
	(*shape)->arg = formatint(integer, (*shape)->flags, (*shape)->type);
	if (!(*shape)->arg)
		return (0);
	return (printf_formatint(fd, (*shape)->arg));
}

int	printhex(int fd, unsigned long num, t_format **shape)
{
	if (!num && (*shape)->type == 'p')
		return (printstring(fd, "(nil)", shape));
	else
		(*shape)->arg = formathex(num, (*shape)->flags, (*shape)->type);
	if (!(*shape)->arg)
		return (0);
	return (printf_formathex(fd, (*shape)->arg));
}
