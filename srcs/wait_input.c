/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:39:43 by dapaulin          #+#    #+#             */
/*   Updated: 2023/04/14 14:31:59 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_prompt(int amount, ...)
{
	int		i;
	char	*prompt;
	char	*tmp;
	va_list	ap;

	i = 0;
	tmp = "";
	prompt = NULL;
	va_start(ap, amount);
	while (i < amount)
	{
		prompt = ft_strjoin(tmp, va_arg(ap, char *));
		if (ft_strlen(tmp))
			free(tmp);
		tmp = prompt;
		i++;
	}
	va_end(ap);
	return (prompt);
}

t_err	wait_input(t_sys_config *mini, int *prop, char *line)
{
	t_err		err;
	static char	*tmp;
	
	err = 0;
	if (tmp)
	{
		mini->str = ft_strjoin(tmp, line);
		free(line);
		free(tmp);	
	}
	else
		mini->str = line;
	err = check_readline(mini->str, mini);
	if (err == ERR_NOLINE && !tmp)
		return (err);
	else if (err == ERR_QUOTES)
	{
		tmp = mini->str;
		*prop = 1;
		return (err);
	}
	*prop = 0;
	tmp = NULL;
	return (err);
}