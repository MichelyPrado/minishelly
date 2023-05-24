/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/24 10:07:04 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_here_doc(t_token *t, char **env)
{
	int		fd;
	int		bkp;
	char	*read_doc;
	char	*file_name;

	read_doc = NULL;
	bkp = dup(1);
	fd = open(HEREDOC_FILE, \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	file_name = t->token[1];
	while (1)
	{
		read_doc = readline(LABEL_HEREDOC);
		search_for_symbol(&read_doc, '$', env);
		if (!read_doc)
		{
			printf(MSG_HEREDOC, file_name);
			return ;
		}
		if (ft_strncmp(read_doc, file_name, ft_strlen(file_name) + 1))
		{
			dup2(fd, 1);
			ft_printf("%s\n", read_doc);
			dup2(bkp, 1);
			if (read_doc)
				free(read_doc);
			read_doc = NULL;
			continue ;
		}
		close(fd);
		break ;
	}
	return ;
}

int	ft_heredoc(t_sys_config *ms)
{
	int				fd;
	int				bkp;
	t_process_func	*func;

	bkp = dup(0);	
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
