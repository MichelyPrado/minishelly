/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 14:53:54 by msilva-p          #+#    #+#             */
/*   Updated: 2022/06/23 22:57:15 by msilva-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_lines(const char *s, char c)
{
	int		is_word;
	size_t	words;

	is_word = 0;
	words = 0;
	while (*s)
	{
		if (!is_word && *s != c)
		{
			is_word = 1;
			words++;
		}
		else if (*s == c)
			is_word = 0;
		s++;
	}
	return (words);
}

static void	ft_count_col(const char *s, char c, char **ret)
{
	size_t	col;
	size_t	i;

	i = 0;
	while (*s)
	{
		col = 0;
		while (s[col] != 0 && s[col] != c)
			col++;
		if (col > 0)
		{
			ret[i] = ft_substr(s, 0, col);
			i++;
		}
		if (col > 0)
			s = s + col;
		else
			s++;
	}
	ret[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ret;

	ret = (char **)malloc((ft_count_lines(s, c) + 1) * sizeof(char *));
	ft_count_col(s, c, ret);
	return (ret);
}
