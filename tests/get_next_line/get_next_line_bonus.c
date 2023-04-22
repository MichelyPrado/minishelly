/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:22:20 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/14 03:59:52 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	g_ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (0);
	while (i < (size -1) && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (0);
}

/*
Copy the structure data to a single array
and return the line.						*/
static char	*create_line(t_buffer **lst, size_t line_size)
{
	char		*line;
	t_buffer	*list;
	size_t		i;
	size_t		len_line;

	list = *lst;
	line = (char *) malloc(line_size * sizeof(char) + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < (line_size + 1) * sizeof(char))
		line[i++] = '\0';
	while (list)
	{
		i = 0;
		len_line = g_ft_strlen(line);
		if ((line_size + 1) <= len_line)
			break ;
		while ((list-> content)[i] && (len_line + 1) < (line_size + 1))
			line[len_line++] = (list-> content)[i++];
		line[len_line] = '\0';
		list = list-> next;
	}
	return (line);
}

int	valid(int fd, char **buf, t_buffer **lst)
{
	int	byte;

	byte = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0))
		return (0);
	if (!(*buf))
	{
		(*buf) = (char *) malloc(BUFFER_SIZE * sizeof(char) + 1);
		if (!(*buf))
			return (0);
		while (byte < (BUFFER_SIZE + 1))
			(*buf)[byte++] = 0;
	}
	g_lstadd_back(lst, 1);
	if (!(*lst))
		return (free((*buf)), 0);
	return (1);
}

/*
Populate and create new nodes with characters from
the file while not finding a \n character or the
end of the file			*/
static size_t	make_pieces(int fd, char *buf, t_buffer **lst, size_t bsr)
{
	size_t	line_size;
	char	*c_pos;
	char	*tmp;

	line_size = 0;
	while (1)
	{
		c_pos = g_ft_strchr(buf, '\n');
		if (c_pos)
			bsr = (c_pos - buf) + 1;
		line_size += bsr;
		(*lst)->content = g_ft_strdup(buf, bsr);
		if (c_pos)
			break ;
		bsr = read(fd, buf, BUFFER_SIZE);
		buf[bsr] = '\0';
		if (!bsr)
			return (line_size);
		g_lstadd_back(lst, 0);
		(*lst) = (*lst)->next;
	}
	tmp = g_ft_strdup(&buf[bsr], g_ft_strlen(&buf[bsr]));
	g_ft_strlcpy(buf, tmp, g_ft_strlen(tmp) + 1);
	free(tmp);
	return (line_size += bsr);
}

char	*get_next_line(int fd)
{
	t_buffer		*lst;
	t_buffer		*ret;
	char			*line;
	size_t			bsr;
	static char		*buf[1024];

	line = NULL;
	if (!valid(fd, &buf[fd], &lst))
		return (NULL);
	ret = lst;
	bsr = g_ft_strlen(buf[fd]);
	if (!bsr)
		bsr = read(fd, buf[fd], BUFFER_SIZE);
	buf[fd][bsr] = '\0';
	bsr = make_pieces(fd, buf[fd], &lst, bsr);
	if (bsr)
		line = create_line(&ret, bsr);
	else
	{
		free(buf[fd]);
		buf[fd] = NULL;
	}
	g_lstclear(&ret, free);
	return (line);
}
