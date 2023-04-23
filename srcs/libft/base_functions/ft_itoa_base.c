/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:31:37 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:56:09 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_itoa_base_count(unsigned long n, int *count, unsigned long base)
{
	char	*ptr;

	if (n >= base)
	{
		*count += 1;
		ptr = ft_itoa_base_count(n / base, count, base);
	}
	else
		ptr = (char *) ft_calloc(*count + 1, sizeof(char));
	return (ptr);
}

static void	ft_itoa_base_aux(unsigned long n, int i, char *p, unsigned long b)
{
	if (n >= b)
		ft_itoa_base_aux(n / b, i - 1, p, b);
	if ((n % b) > 9)
		p[i] = ((n % b) - 10) + 'a';
	else
		p[i] = (n % b) + '0';
}

char	*ft_itoa_base(unsigned long n, int base)
{
	char	*ptr;
	int		count;

	count = 1;
	ptr = ft_itoa_base_count(n, &count, base);
	ft_itoa_base_aux(n, count -1, ptr, base);
	return (ptr);
}
