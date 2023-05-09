/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:05:08 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/08 14:03:06 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

ssize_t	find_key(char *line, char **env, int *i)
{
	int		pos;
	char	*tmp;

	tmp = NULL;
	while (line[*i] && line[*i] != 32 && line[*i] != 9)
		*i += 1;
	tmp = ft_strndup(&line[1], (*i) - 1);
	pos = search_envp(env, tmp);
	if (tmp)
		free(tmp);
	return (pos);
}

// void	test(ssize_t pos, char *line, int i, char **env)
// {
// 	char	*start;
// 	char	*middle;
// 	char	*end;

// 	start = ft_strndup(*line, i);
// 	middle = ft_strdup("");
// 	if (pos >= 0)
// 		middle = ft_strdup(&env[pos][keylen(env[pos]) + 1]);
// 	end = line[i];
// 	*line = create_prompt(3, start, middle, end);
// }

void	expand_symbol(char **line, char c, char **env)
{
	int		j;
	int		i;
	ssize_t	pos;
	char	*end;
	char	*start;
	char	*middle;

	i = 0;
	j = 0;
	pos = -1;
	start = NULL;
	middle = NULL;
	end = NULL;
	if (!*line)
		return ;
	while ((*line)[i])
	{
		if ((*line)[i] == c)
		{
			j = 0;
			pos = find_key(&(*line)[i], env, &j);
			start = ft_strndup(*line, i);
			if (pos >= 0)
				middle = ft_strdup(&env[pos][keylen(env[pos]) + 1]);
			else
				middle = ft_strdup("");
			end = create_prompt(3, start, middle, &(*line)[i + j]);
			if (*line)
				free(*line);
			if (start)
				free(start);
			if (middle)
				free(middle);
			*line = end;
		}
		i++;
	}
}
