/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:05:08 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/12 12:50:39 by dapaulin         ###   ########.fr       */
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

void	free_mult_strs(char **strs)
{
	int	i;

	i = 0;
	if (strs)
	{
		while (strs[i])
		{
			free(strs[i]);
			strs[i] = NULL;
			i++;
		}
	}
}

void	expand_symbol(int i, char **line, char **env, char **pieces)
{
	int		j;
	ssize_t	pos;

	j = 0;
	pos = find_key(&(*line)[i], env, &j);
	pieces[0] = ft_strndup(*line, i);
	if (pos >= 0)
		pieces[1] = ft_strdup(&env[pos][keylen(env[pos]) + 1]);
	else
		pieces[1] = ft_strdup("");
	pieces[2] = (*line);
	*line = create_prompt(3, pieces[0], pieces[1], &pieces[2][i + j]);
	free_mult_strs(pieces);
}

void	search_for_symbol(char **line, char c, char **env)
{
	int		j;
	int		i;
	ssize_t	pos;
	char	**pieces;

	i = 0;
	j = 0;
	pos = -1;
	if (!*line)
		return ;
	pieces = ft_calloc(4, sizeof(char *));
	while ((*line)[i])
	{
		if ((*line)[i] == c)
			expand_symbol(i, line, env, pieces);
		i++;
	}
	if (pieces)
		free(pieces);
}
