/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 11:39:43 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 17:14:22 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*create_prompt(int amount, ...)
{
	int		i;
	char	*str;
	char	*prompt;
	char	*tmp;
	va_list	ap;

	i = 0;
	tmp = NULL;
	prompt = NULL;
	va_start(ap, amount);
	while (i < amount)
	{
		str = va_arg(ap, char *);
		if (!str)
			str = "";
		prompt = ft_strjoin(tmp, str);
		if (tmp)
			free(tmp);
		tmp = prompt;
		i++;
	}
	va_end(ap);
	return (prompt);
}

int	check_no_inputs(t_sys_config *mini, char *line, char *tmp)
{
	if (!line)
		ft_ctrl_d(mini);
	if (!ft_strlen(line) && !tmp)
	{
		if (line)
			free(line);
		return (ONLY_ENTER);
	}
	return (0);
}

t_err	i_hate_you_norm(t_sys_config *mini, char **tmp, int *prop)
{
	t_err	err;

	err = check_readline(mini->str, mini);
	if (err == ERR_NOLINE && !*tmp)
		return (err);
	else if (err == ERR_QUOTES)
	{
		*tmp = mini->str;
		*prop = 1;
		return (err);
	}
	*prop = 0;
	*tmp = NULL;
	return (err);
}

t_err	wait_input(t_sys_config *mini, int *prop, char *line)
{
	t_err		err;
	static char	*tmp;

	err = 0;
	if (check_no_inputs(mini, line, tmp))
		return (ONLY_ENTER);
	if (tmp)
	{
		mini->str = create_prompt(3, tmp, "\n", line);
		if (line)
			free(line);
		if (line)
			free(tmp);
	}
	else
		mini->str = line;
	err = i_hate_you_norm(mini, &tmp, prop);
	return (err);
}
