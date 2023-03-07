/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/07 16:49:34 by dapaulin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//  printf()
# include <stdio.h>

//  malloc()  free()  exit()  getenv()
# include <stdlib.h>

//  signal()  sigaction()  sigemptyset()  sigaddset()  kill()
# include <signal.h>

//  write()  access()  read() close()  fork()  getcwd()  chdir()  unlink()
//  execve()  dup()  dup2()  pipe()  isatty()  ttyname() ttyslot()
# include <unistd.h>

//  strerror()
# include <string.h>

//  perror()
# include <errno.h>

//  readline()  rl_clear_history()  rl_on_new_line()  rl_replace_line()
//  rl_redisplay()  add_history()
# include <readline/readline.h>
# include <readline/history.h>

//  open()  stat()  lstat()  fstat()
# include <fcntl.h>
# include <sys/stat.h>

//  wait()  waitpid()  wait3()  wait4()
# include <sys/wait.h> 

//  opendir()  readdir()  closedir()
# include <dirent.h>
# include <sys/types.h>

//  ioctl()
# include <sys/ioctl.h>

//  tcsetattr()  tcgetattr()
# include <termios.h>

//  tgetent()  tgetflag()  tgetnum()  tgetstr()  tgoto()  tputs()
# include <curses.h>
# include <term.h>

//  libft
# include "./libft/libft.h"

typedef struct s_minishelly
{
	char *str;
	char **e;
	char **path;
}	t_minishelly;

void		exit_check(char *str);

// Get Envp
int			count_str_envp(char **envp);
void		get_envp(char **envp, t_minishelly *data);
void		split_paths(char **env, t_minishelly *data);

// Parser
char    	*split_pipe(char *str, char c);

#endif