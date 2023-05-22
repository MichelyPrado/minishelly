/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:51:33 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 03:03:47 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	normal_exit(void (*f)(void *), int exit_code, void *item)
{
	f(item);
	ft_putstr_fd(strerror(exit_code), 2);
	write(2, "\n", 1);
	exit(exit_code);
}

void	sys_exit(void (*f)(t_sys_config *), int exit_code, t_sys_config *mini)
{
	f(mini);
	ft_printf("%s\n", strerror(exit_code));
	exit(exit_code);
}

void	sys_exit_err(void (*f)(t_sys_config *), t_sys_config *mini, char *msg)
{
	f(mini);
	if (!msg)
	{
		ft_putstr_fd(strerror(*get_status_code()), 2);
		write(2, "\n", 1);
	}
	else
	{
		ft_putstr_fd(msg, 2);
		write(2, "\n", 1);
	}
	if (mini)
		free(mini);
	exit (*get_status_code());
}
