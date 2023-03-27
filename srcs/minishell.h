/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/27 19:02:10 by dapaulin         ###   ########.fr       */
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

# define SQUOTE 39
# define DQUOTE 34
# define NO_PRINT '*'
# define CHAR_NULL 1
# define MORE_ONE_SPACE 2

typedef struct s_token
{
	char			**cmds;
	char			*operator;
	char			type;
	void			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_sys_config
{
	char	*str;
	char	**env;
	int		nlen_parser;
	char	*new_parser;
	char	**path;
}	t_sys_config;

void		exit_check(char *str);

// Get Envp
void		get_envp(char **envp, t_sys_config *data);
void		ft_export(t_sys_config *mini, char *key, char *value);
void		ft_unset(t_sys_config *mini, char *key);
int			edit_envp(t_sys_config *mini, char *key, char *new_value);
ssize_t		search_envp(char **envp, char *key);

// Env Utils
int			amount_vars(char **envp);
char		**alloc_env(char **env, int slots);
void		clean_env(char **new_envp);
int			env_empty(t_sys_config *mini, char *key, char *value);
size_t		keylen(char *var_env);
char		*join_key_value(char *key, char *value); // trocar por ft_strjoin

// Handle  Path
void		split_paths(char **env, t_sys_config *data);

// Parser
int			add_character(char *dst, int j, char c);
void		symbol_delimiter(char *src, t_sys_config *mini);
int			count_delimiter(char *str);
int			add_delimiters(char symbol, int *j, char *dst, char *actual_char);
int			check_next(char symbol, char *str);

#endif