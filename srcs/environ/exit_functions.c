/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 21:51:33 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/12 13:33:22 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	normal_exit(void (*f)(void *), int exit_code, void *item)
{
	f(item);
	printf("%s\n", strerror(exit_code));
	exit(exit_code);
}

void	sys_exit(void (*f)(t_sys_config *), int exit_code, t_sys_config *mini)
{
	f(mini);
	ft_printf("%s\n", strerror(exit_code));
	exit(exit_code);
}
