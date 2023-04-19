/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 17:32:29 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:36:14 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	sub_atoi(const char *strnum, int *size)
{
	int		i;
	char	*flag;
	int		num;

	i = 0;
	num = 0;
	while (ft_isdigit(strnum[i]))
		i++;
	if (i > 0)
	{
		flag = ft_strndup(strnum, i);
		*size += i;
		num = ft_atoi(flag);
		if (flag)
			free(flag);
	}
	return (num);
}

t_bool	ft_isflag(char flag, char c, int *i)
{
	if (c == flag)
		return (*i += 1, t);
	return (f);
}

int	print_spaces(int fd, int *bytes, char c)
{
	int	bsr;

	bsr = 0;
	while (*bytes > 0)
	{
		bsr += ft_putchar_fd(c, fd);
		*bytes -= 1;
	}
	return (bsr);
}

unsigned int	convert_num(int num, char signal)
{
	if (signal == '-')
		return (num * -1);
	return (num * 1);
}

size_t	ft_strlen_upper(char *str)
{
	int	size;

	size = 0;
	while (str[size])
	{
		if (ft_islower(str[size]))
			str[size] -= 32;
		size++;
	}
	return (size);
}
