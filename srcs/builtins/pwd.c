/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 18:18:05 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/17 20:04:48 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     ft_pwd(t_sys_config *mini)
{
    char    *pwd;

    pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
    if (pwd)
	    free(pwd);
	return (0);
    if (mini)
        return (0);
}
