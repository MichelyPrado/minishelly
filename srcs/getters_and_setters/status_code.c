/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_code.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 02:23:39 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/20 12:11:56 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*get_status_code(void)
{
	static int	status_code;

	return (&status_code);
}

void	set_status_code(int status_code)
{
	int	*sc;

	sc = get_status_code();
	*sc = status_code;
}
