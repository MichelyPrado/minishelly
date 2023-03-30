/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msilva-p <msilva-p@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/03/30 19:03:14 by msilva-p         ###   ########.fr       */
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

//======== Define types ========\\/
typedef enum e_types
{
	OP_AND,
	OP_OR,
	OP_PIPE,
	OP_OUTPUT,
	OP_INPUT,
	OP_UNTIL,
	OP_APPEND,
	OP_CMD
}	t_types;

typedef struct s_token
{
	char			**cmds;
	char			*operator;
	int				type;
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

// Handle Env
void		ft_unset(t_sys_config *mini, char *key);
void		ft_export(t_sys_config *mini, char *key, char *value);
ssize_t		search_envp(char **envp, char *key);
int			edit_envp(t_sys_config *mini, char *key, char *new_value);
void		get_envp(char **envp, t_sys_config *data);

// Env Utils
int			amount_vars(char **envp);
size_t		keylen(char *var_env);
void		clean_env(char **new_envp);
char		**alloc_env(char **env, int slots);
int			env_empty(t_sys_config *mini, char *key, char *value);

// Tools Box
char		*join_key_value(char *key, char *value); // trocar por ft_strjoin

// Handle  Path
void		split_paths(char **env, t_sys_config *data);

// Parser
int			add_delimiters(char symbol, int *j, char *dst, char *actual_char);
void		symbol_delimiter(char *src, t_sys_config *mini);
int			count_delimiter(char *str);

// Parser Utils
int			add_character(char *dst, int j, char c);
int			check_next(char symbol, char *str);
int			check_quotes(char *src, char quote, int *i);
int			jump_quotes(char *src, t_sys_config *mini, char quote, int *i);

// List Token
t_token		*ft_token_new(char **cmds, char *operator, int type);
t_token		*ft_token_last(t_token *node);
void		ft_token_add_end(t_token **node, t_token *new);
void		free_cmds(char **cmds);
void		ft_token_free(t_token **node);

#endif