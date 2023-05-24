/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 15:47:29 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_the_label(char **read_doc, char *file_name, int *fd)
{
	if (ft_strncmp(*read_doc, file_name, ft_strlen(file_name) + 1))
	{
		dup2(*fd, 1);
		ft_printf("%s\n", *read_doc);
		dup2(*get_fd_bkp_out(), 1);
		if (*read_doc)
			free(*read_doc);
		*read_doc = NULL;
		return (0);
	}
	return (1);
}

int	has_heredoc(t_token *t, char **env)
{
	int	has;

	has = 0;
	while (t && t->type != OP_PIPE)
	{
		if (t->type == OP_UNTIL)
			run_here_doc(t, env);
		t = t->next;
	}
	return (has);
}

void	run_here_doc(t_token *t, char **env)
{
	int		fd;
	char	*read_doc;

	read_doc = NULL;
	fd = open(HEREDOC_FILE, \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		read_doc = readline(LABEL_HEREDOC);
		search_for_symbol(&read_doc, '$', env);
		if (!read_doc)
		{
			printf(MSG_HEREDOC, t->token[1]);
			return ;
		}
		if (!is_the_label(&read_doc, t->token[1], &fd))
			continue ;
		close(fd);
		break ;
	}
	return ;
}

int	ft_heredoc(t_sys_config *ms)
{
	int				fd;
	t_process_func	*func;

	func = ms->exec->func;
	fd = open(HEREDOC_FILE, O_RDONLY);
	if (ms->tokens->next)
	{
		ms->tokens = ms->tokens->next;
		if (dup_fd_in(fd) == -1)
			sys_exit_err(clean_data, ms, NULL);
		close(fd);
		if (func[ms->tokens->type](ms))
			return (1);
		if (ms->exec->pid == 0)
			close_fds(ms);
		close(0);
		if (dup2(*get_fd_bkp_in(), 0) == -1)
			sys_exit(clean_data, EBADF, ms);
	}
	unlink(HEREDOC_FILE);
	return (0);
}
