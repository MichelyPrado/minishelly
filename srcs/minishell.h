/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/20 19:47:22 by msilva-p         ###   ########.fr       */
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

# define NO_PRINT '*'

typedef struct s_minishelly
{
	char	*str;
	char	**e;
	char	**path;
}	t_minishelly;

void		exit_check(char *str);

// Envp Utils
size_t		keylen(char *var_env);
int			count_vars(char **envp);
void		clean_env(char **new_envp);
char		**alloc_envp(t_minishelly *mini, int space);

// Handle Env
void		ft_unset(t_minishelly *mini, char *key);
void		ft_export(t_minishelly *mini, char *key, char *value);
ssize_t		search_envp(char **envp, char *key);
void		edit_envp(t_minishelly *mini, char *key, char *new_value);
void		get_envp(char **envp, t_minishelly *data);

// slice
void		slice_add(t_minishelly *mini, char **aux, char *key, char *value);
void		slice_unset(t_minishelly *mini, char *key, char **aux);

// handle path
void		split_paths(char **env, t_minishelly *data);

// Parser
int			add_no_printable(char *s, int i, int j, char c);
char		*symbol_delimiter(char *str);
int			count_delimiter(char *str);
int			add_delimiters(char symbol, int *c_pipe, char *s, char *str);

#endif