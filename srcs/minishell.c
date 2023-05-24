/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 13:44:11 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 16:21:14 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_fd;

int	main(int argc, char **argv)
{
	extern char	**environ;

	return (minishelly(argc, argv, environ));
}
