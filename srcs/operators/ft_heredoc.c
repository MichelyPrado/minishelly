/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 05:13:56 by dapaulin          #+#    #+#             */
/*   Updated: 2023/05/22 22:46:56 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_here_doc(t_sys_config *ms)
{
	int		fd;
	int		bkp;
	char	*read_doc;
	char	*file_name;

	read_doc = NULL;
	bkp = dup(1);
	fd = open(HEREDOC_FILE, \
	O_WRONLY | O_CREAT | O_TRUNC, 0644);
	file_name = ms->tokens->token[1];
	while (1)
	{
		read_doc = readline(LABEL_HEREDOC);
		search_for_symbol(&read_doc, '$', ms->env);
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

void	heredoc_output(t_sys_config *ms)
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
		dup2(fd, 0);
		close(fd);
		func[ms->tokens->type](ms);
		if (ms->exec->pid == 0)
			close_fds(ms);
		close(0);
		dup2(bkp, 0);
	}
	unlink(HEREDOC_FILE);
}

int	ft_heredoc(t_sys_config *ms)
{
	run_here_doc(ms);
	if (ms->tokens->next && ms->tokens->next->type != OP_UNTIL)
		heredoc_output(ms);
	return (0);
}
