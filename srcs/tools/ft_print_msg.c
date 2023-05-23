/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_msg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 03:50:01 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 02:56:42 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_err(int status_code, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	else if (status_code == 127)
		ft_putstr_fd(" No such file or directory\n", 2);
	else if (status_code == 1)
		ft_putstr_fd(" command not found\n", 2);
	set_status_code(status_code);
}
