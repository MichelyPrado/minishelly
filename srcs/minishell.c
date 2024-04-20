/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:44:11 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/25 20:02:25 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_fd;

int	main(int argc, char **argv)
{
	extern char	**environ;

	g_fd = 1;
	return (minishelly(argc, argv, environ));
}
