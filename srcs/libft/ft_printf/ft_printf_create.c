/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 20:31:54 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:36:04 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_format	*new_format(void)
{
	t_format	*c_format;

	c_format = (t_format *) malloc(sizeof(t_format));
	if (!c_format)
		return (NULL);
	c_format->arg = NULL;
	c_format->flags = NULL;
	c_format->f_pos = 0;
	c_format->type = '\0';
	return (c_format);
}

t_typechar	*new_typechar(char c)
{
	t_typechar	*c_format;

	c_format = (t_typechar *) malloc(sizeof(t_format));
	if (!c_format)
		return (NULL);
	c_format->value = c;
	c_format->minus = f;
	c_format->bytes = 0;
	c_format->valid_bytes = 0;
	return (c_format);
}

t_typestring	*new_typestring(void)
{
	t_typestring	*c_format;

	c_format = (t_typestring *) malloc(sizeof(t_typestring));
	if (!c_format)
		return (NULL);
	c_format->space = f;
	c_format->minus = f;
	c_format->bytes = 0;
	c_format->dot = f;
	c_format->bytes_s = 0;
	c_format->valid_bytes = 0;
	c_format->value = NULL;
	return (c_format);
}

t_typeint	*new_typeint(unsigned int num, char signal)
{
	t_typeint	*c_format;

	c_format = (t_typeint *) malloc(sizeof(t_typeint));
	if (!c_format)
		return (NULL);
	c_format->fzero = f;
	c_format->space = f;
	c_format->plus = f;
	c_format->signal = signal;
	c_format->value = num;
	c_format->minus = f;
	c_format->bytes = 0;
	c_format->dot = f;
	c_format->bytes_s = 0;
	c_format->valid_bytes = 0;
	return (c_format);
}

t_typehex	*new_typehex(unsigned long num, char caset)
{
	t_typehex	*c_format;

	c_format = (t_typehex *) malloc(sizeof(t_typehex));
	if (!c_format)
		return (NULL);
	c_format->minus = f;
	c_format->fzero = f;
	c_format->bytes = 0;
	c_format->dot = f;
	c_format->bytes_s = f;
	c_format->valid_bytes = 0;
	if (caset == 'p')
	{
		c_format->value = num;
		c_format->hash = t;
		c_format->caset = 'x';
		return (c_format);
	}
	c_format->value = (unsigned int)num;
	c_format->hash = f;
	c_format->caset = caset;
	return (c_format);
}
