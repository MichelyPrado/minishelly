/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_formats.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:07:55 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:36:06 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_typechar	*formatchar(char c, const char *flags)
{
	int			i;
	t_typechar	*format;

	i = 0;
	format = new_typechar(c);
	if (!format)
		return (NULL);
	format->minus = ft_isflag('-', flags[i], &i);
	while (flags[i] == '-')
		i++;
	format->bytes = sub_atoi(&flags[i], &i);
	format->valid_bytes = i;
	return (format);
}

t_typestring	*formatstring(char *str, const char *flags)
{
	int				i;
	t_typestring	*format;

	i = 0;
	format = new_typestring();
	if (!format)
		return (NULL);
	format->space = ft_isflag(' ', flags[i], &i);
	format->minus = ft_isflag('-', flags[i], &i);
	while (flags[i] == '-')
		i++;
	format->bytes = sub_atoi(&flags[i], &i);
	format->dot = ft_isflag('.', flags[i], &i);
	format->bytes_s = sub_atoi(&flags[i], &i);
	format->valid_bytes = i;
	if (!str && (format->bytes_s < 6 && format->bytes_s > 0))
		format->value = ft_strdup("");
	else if (!str)
		format->value = ft_strdup("(null)");
	else
		format->value = ft_strdup(str);
	return (format);
}

t_typeint	*formatint(int integer, const char *flags, char type)
{
	int				i;
	char			signal;
	t_typeint		*format;

	i = 0;
	if (integer < 0)
		signal = '-';
	else
		signal = '+';
	if (type == 'u')
		format = new_typeint(integer, 0);
	else
		format = new_typeint(convert_num(integer, signal), signal);
	if (!format)
		return (NULL);
	i += match_iflags((char *)&flags[i], &format->fzero, &format, '0');
	i += match_iflags((char *)&flags[i], &format->minus, &format, '-');
	format->bytes = sub_atoi(&flags[i], &i);
	format->dot = ft_isflag('.', flags[i], &i);
	format->bytes_s = sub_atoi(&flags[i], &i);
	format->valid_bytes = i;
	return (format);
}

t_typehex	*formathex(unsigned long num, const char *flags, char caset)
{
	int			i;
	t_typehex	*format;

	i = 0;
	format = new_typehex(num, caset);
	if (!format)
		return (NULL);
	i += match_xflags((char *)&flags[i], &format->fzero, &format->hash, '0');
	i += match_xflags((char *)&flags[i], &format->minus, &format->hash, '-');
	format->bytes = sub_atoi(&flags[i], &i);
	format->dot = ft_isflag('.', flags[i], &i);
	format->bytes_s = sub_atoi(&flags[i], &i);
	format->valid_bytes = i;
	return (format);
}
