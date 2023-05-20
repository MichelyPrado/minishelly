/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 03:50:01 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/19 16:13:49 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_err(int status_code, char *msg)
{
	if (status_code == 127)
		ft_putstr_fd(" No such file or directory", 2);
	else 
		ft_putstr_fd(msg, 2);
	set_status_code(status_code);
}
