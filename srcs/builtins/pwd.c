/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:18:05 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 06:55:45 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_sys_config *mini)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		set_status_code(EINVAL);
		return (1);
	}
	ft_printf("%s\n", pwd);
	set_status_code(0);
	if (pwd)
		free(pwd);
	return (0);
	(void)(mini);
}
