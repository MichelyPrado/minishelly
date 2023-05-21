/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/21 20:27:14 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	run_here_doc(t_sys_config *ms)
{
	int		size;
	char	*read_doc;
	char	*file_name;

	size = 0;
	read_doc = NULL;
	file_name = ms->tokens->token[1];
	while (1) {
		read_doc = readline(LABEL_HEREDOC);
		search_for_symbol(&read_doc, '$', ms->env);
		if (!read_doc)
		{
			printf(MSG_HEREDOC, file_name);
			return (0);
		}
		if (ft_strncmp(read_doc, file_name, ft_strlen(file_name) + 1))
		{
			dup2(*get_fd(), 1);
			ft_printf("%s\n", read_doc);
			dup2(*get_fd_bkp(), 1);
			size += ft_strlen(read_doc) + 1;
			if (read_doc)
				free(read_doc);
			read_doc = NULL;
			continue ;
		}
		close(*get_fd());
		break ;
	}
	return (size);
}

void	heredoc_output(t_sys_config *ms, int size)
{
	int				fd;
	t_process_func	*func;
	char			*read_doc;

	read_doc = NULL;
	func = ms->exec->func;
	fd = open(HEREDOC_FILE, O_RDONLY | O_CREAT);
	*get_fd() = fd;
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		dup2(*get_fd(), 0);
		close(*get_fd());
		func[ms->tokens->type](ms);
		close(0);
		dup2(*get_fd_bkp(), 0);
	} 
	else
	{
		read_doc = ft_calloc(sizeof(char), size + 1);
		read(*get_fd(), read_doc, size + 1);
		printf("%s", read_doc);
	}
	unlink(HEREDOC_FILE);
}

int ft_heredoc(t_sys_config *ms)
{
	int				fd;
	int				size;

	size = 0;
	*get_fd_bkp() = dup(1);
	fd = open(HEREDOC_FILE, \
	O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, S_IRWXU);
	*get_fd() = fd;
	size = run_here_doc(ms);
	heredoc_output(ms, size);
	*get_fd_bkp() = dup(0);
	return (0);
}