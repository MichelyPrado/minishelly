/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/20 21:04:43 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int test_heredoc(t_sys_config *ms)
{
	int				size;
	int				fd;
	int				bkp;
	char			*read_doc;
	t_process_func	*func;

	bkp = dup(1);
	size = 0;
	func = ms->exec->func;
	fd = open("./.heredoc", O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	while (1) {
		read_doc = readline("heredoc> ");
		if (!read_doc)
		{
			printf("\nwarning: here-document delimited by end-of-file (wanted '%s')\n", ms->tokens->token[1]);
			return (1);
		}
		if (ft_strncmp(read_doc, ms->tokens->token[1], ft_strlen(ms->tokens->token[1]) + 1))
		{
			dup2(fd, 1);
			printf("%s\n", read_doc);
			dup2(bkp, 1);
			size += ft_strlen(read_doc) + 1;
			free(read_doc);
			read_doc = NULL;
			continue ;
		}
		close(fd);
		break ;
	}
	bkp = dup(0);
	fd = open("./.heredoc", O_RDONLY);
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		dup2(fd, 0);
		close(fd);
		func[ms->tokens->type](ms);
		close(0);
		dup2(bkp, 0);
	} 
	else
	{
		read_doc = ft_calloc(sizeof(char), size + 1);
		read(fd, read_doc, size + 1);
		printf("%s", read_doc);
	}
	unlink(".heredoc");
	return (0);
}