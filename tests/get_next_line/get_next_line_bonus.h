/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 19:22:31 by dapaulin          #+#    #+#             */
/*   Updated: 2023/03/13 23:58:35 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

typedef struct a_buffer
{
	char			*content;
	struct a_buffer	*next;
}	t_buffer;

// String Manipulation
size_t		g_ft_strlen(const char *str);
char		*g_ft_strchr(const char *src, int c);
size_t		g_ft_strlcpy(char *dest, const char *src, size_t size);
char		*g_ft_strdup(const char *s, size_t size);
// List Manipulation
void		g_lstadd_back(t_buffer **lst, int creat_lst);
void		g_lstclear(t_buffer **lst, void (*del)(void *));
// GNL Actions
char		*get_next_line(int fd);
#endif
