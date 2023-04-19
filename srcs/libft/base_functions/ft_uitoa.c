/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:31:55 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/19 11:55:43 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_uitoa_count(unsigned int n, int *count)
{
	char	*ptr;

	if (n >= 10)
	{
		*count += 1;
		ptr = ft_uitoa_count(n / 10, count);
	}
	else
		ptr = (char *) ft_calloc(*count + 1, sizeof(char));
	return (ptr);
}

static void	ft_uitoa_aux(unsigned int n, int count, char *ptr)
{
	if (n >= 10)
		ft_uitoa_aux(n / 10, count - 1, ptr);
	ptr[count] = (n % 10) + '0';
}

char	*ft_uitoa(unsigned int n)
{
	char	*ptr;
	int		count;

	count = 1;
	ptr = ft_uitoa_count(n, &count);
	ft_uitoa_aux(n, count -1, ptr);
	return (ptr);
}
