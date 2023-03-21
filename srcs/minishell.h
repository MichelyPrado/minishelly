/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/20 21:47:02 by dapaulin         ###   ########.fr       */
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
# define CHAR_NULL 1
# define MORE_ONE_SPACE 2

typedef struct s_minishelly
{
	char	*str;
	char	**e;
	char	**path;
}	t_minishelly;

void		exit_check(char *str);

// Get Envp
void		get_envp(char **envp, t_minishelly *data);
void		ft_export(t_minishelly *mini, char *key, char *value);
void		ft_unset(t_minishelly *mini, char *key);
int			edit_envp(t_minishelly *mini, char *key, char *new_value);
ssize_t		search_envp(char **envp, char *key);

// Env Utils
int			amount_vars(char **envp);
char		**alloc_env(char **env, int slots);
void		clean_env(char **new_envp);
int			env_empty(t_minishelly *mini, char *key, char *value);
size_t		keylen(char *var_env);
char		*join_key_value(char *key, char *value); // trocar por ft_strjoin

// Handle  Path
void		split_paths(char **env, t_minishelly *data);

// Parser
int			add_character(char *s, int i, int j, char c);
char		*symbol_delimiter(char *str);
int			count_delimiter(char *str);
int			add_delimiters(char symbol, int *c_pipe, char *s, char *str);

#endif