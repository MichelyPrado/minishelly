/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:05:08 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/16 03:34:19 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

ssize_t	find_key(char *line, char **env, int *i)
{
	int		pos;
	char	*tmp;

	tmp = NULL;
	*i += 1;
	while (line[*i] && (is_valid_char_for_var(line[*i])
		|| ft_isdigit(line[*i])))
		*i += 1;
	tmp = ft_strndup(&line[1], (*i) - 1);
	pos = search_envp(env, tmp);
	if (tmp)
		free(tmp);
	return (pos);
}

void	expand_symbol(int i, char **line, char **env, char **pieces)
{
	int		j;
	ssize_t	pos;

	j = 0;
	pieces[0] = ft_strndup(*line, i);
	if (!env)
	{
		pieces[1] = ft_itoa(*get_status_code());
		j = 2;	
	}
	else
	{	
		pos = find_key(&(*line)[i], env, &j);
		if (pos >= 0)
			pieces[1] = ft_strdup(&env[pos][keylen(env[pos]) + 1]);
		else
			pieces[1] = ft_strdup("");
	}
	pieces[2] = (*line);
	*line = create_prompt(3, pieces[0], pieces[1], &pieces[2][i + j]);
	clean_lstitens(pieces);
}

int	check_single_quotes(char *line)
{
	static int	dq;
	char		*p;

	p = NULL;
	if (*line == '\"')
	{
		if (dq == 0)
			dq = 1;
		else
			dq = 0;
	}
	else if (dq == 0 && *line == '\'')
	{
		p = ft_strchr(&line[1], '\'');
		if (p)
			return (p - line);
	}
	return (0);
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
		i += check_single_quotes(&(*line)[i]);
		if ((*line)[i] == c)
		{
			if (is_valid_char_for_var((*line)[i + 1]))
				expand_symbol(i, line, env, pieces);
			else if(check_next_eq('?', &(*line)[i]))
				expand_symbol(i, line, NULL, pieces);
		}
		i++;
	}
	if (pieces)
		free(pieces);
}
