/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/04/17 16:07:41 by dapaulin         ###   ########.fr       */
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

# define L_RED "\033[0;31m"
# define L_REDB "\033[1;31m"
# define L_WHITE "\033[0;37m"
# define L_WHITEB "\033[1;37m"
# define L_YELLOW "\033[0;33m"
# define L_YELLOWB "\033[1;33m"
# define L_BLUE "\033[0;34m"
# define L_GREEN "\033[0;32m"
# define L_GREENB "\033[1;32m"

# define SHELLNAME "Minishelly:"
# define PROPQUOTE "quote"
# define PROP "> "

# define SQUOTE 39
# define DQUOTE 34
# define NO_PRINT '*'
# define CHAR_NULL 1
# define MORE_ONE_SPACE 2

//typedef t_err (*t_function)(t_sys_config *);

// DEFINE ERRORS
typedef enum e_err
{
	NO_ERR = 0,
	ERR_QUOTES = 256,
	ERR_NOLINE
}	t_err;

//======== Define types ========\\/
typedef enum e_types
{
	OP_DEFAULT = 0,
	OP_AND = 1,
	OP_OR = 2,
	OP_PIPE = 3,
	OP_OUTPUT = 4,
	OP_INPUT = 5,
	OP_UNTIL = 6,
	OP_APPEND = 7,
	OP_CMD = 8,
	OP_EXIT = 9,
	OP_CD = 10,
	OP_ENV = 11,
	OP_UNSET = 12,
	OP_EXPORT = 13,
	OP_PWD = 14,
	OP_ECHO = 15
}	t_types;

typedef struct s_keyword_map
{
	char		*keyword;
	t_types		type;
}				t_keyword_map;

typedef struct s_token
{
	char			**token;
	t_types			type;
	struct s_token	*next;
}	t_token;

typedef struct s_sys_config
{
	char	*str;
	char	**env;
	int		nlen_parser;
	char	*new_parser;
	t_token	*tokens;
	char	**prompt;
	char	**path;
}	t_sys_config;

typedef int (*process_function)(t_sys_config *);

// Sys Config

t_sys_config *start_sys();

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
t_err		check_readline(char *src, t_sys_config *mini);
int			count_delimiter(char *str);

// Parser Utils
int			add_character(char *dst, int j, char c);
int			check_next(char symbol, char *str);
int			check_quotes(char *src, char quote, int jump);
int			jump_quotes(char *src, t_sys_config *mini, char quote, int *j);

// List Token
t_token		*ft_token_new(char **cmds, int type);
t_token		*ft_token_last(t_token *node);
void		ft_token_add_end(t_token **node, t_token *new);
void		free_cmds(char **cmds);
void		ft_token_free(t_token **node);

// handle tokens
t_token		*ft_create_tokens(t_sys_config *mini);
t_types		tag_token(char *cmd);
int			ft_isspace(char *str);
char		*ft_token_repair(char *token);

// Wait input
char		*create_prompt(int amount, ...);
t_err		wait_input(t_sys_config *mini, int *prop, char *line);

// HASH
int			hash_func(char *cmd, t_keyword_map *keymap);

// Process
void		exec_commands(t_sys_config *mini);

#endif