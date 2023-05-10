/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:47:13 by msilva-p          #+#    #+#             */
/*   Updated: 2023/05/10 12:32:19 by dapaulin         ###   ########.fr       */
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
# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

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
# define NO_PRINT -1
# define CHAR_NULL 1
# define MORE_ONE_SPACE 2

//typedef t_err (*t_function)(t_sys_config *);

// DEFINE ERRORS
typedef enum e_err
{
	NO_ERR = 0,
	ONLY_ENTER,
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

typedef enum e_first_or_end
{
	BFALSE,
	BTRUE
}			t_first_or_end;

typedef struct s_exec
{
	int				i;
	int				pipes;
	int				pid;
	int				**fd;
	int				status;
	t_first_or_end	flag;
	void			*func;
}				t_exec;

typedef struct s_sys_config
{
	char	*str;
	char	**env;
	int		nlen_parser;
	char	*new_parser;
	t_token	*tokens;
	char	**prompt;
	t_exec	*exec;
	char	**path;
	int		exit_status;
}	t_sys_config;

# define NUM_FUNCS 16
typedef int	(*t_process_func)(t_sys_config *);
typedef struct sigaction	t_sa;



// Sys Config
char			*cat_user(char **env);
t_sys_config	*start_sys(char **environ);
void			update_unbound_vars(char *key, t_sys_config *mini);
void			clean_sys(t_sys_config *mini);
void			clean_strlist(char ***strs);

// Handle Env
void			ft_unset(t_sys_config *mini, char *key);
void			ft_export(char ***env, char *key, char *value);
ssize_t			search_envp(char **envp, char *key);
int				edit_envp(char ***env, char *key, char *new_value);
void			get_envp(char **envp, t_sys_config *data);

// Env Utils
int				amount_vars(char **envp);
size_t			keylen(char *var_env);
void			clean_env(char **new_envp);
char			**alloc_env(char **env, int slots);
int				env_empty(char ***env, char *key, char *value);

// Tools Box
char			*join_key_value(char *key, char *value);

// Handle  Path
char			**split_paths(char **env);
int				cmd_path_valid(char **token, char **path);

// Parser
int				add_delimiters(char symbol, int *j, char *dst, char *c);
t_err			check_readline(char *src, t_sys_config *mini);
int				count_delimiter(char *str);

// Parser Utils
int				add_character(char *dst, int j, char c);
int				check_next(char symbol, char *str);
int				check_quotes(char *src, char quote, int jump);
int				jump_quotes(char *src, t_sys_config *mini, char quote, int *j);

// List Token
t_token			*ft_token_new(char **cmds, int type);
t_token			*ft_token_last(t_token *node);
void			ft_token_add_end(t_token **node, t_token *new);
void			free_cmds(char **cmds);
void			ft_token_free(t_token **node);

// handle tokens
t_token			*ft_create_tokens(t_sys_config *mini);
t_types			tag_token(char *cmd);
int				ft_isspace(char *str);
char			*ft_token_repair(char *token);

// Wait input
t_err			wait_input(t_sys_config *mini, int *prop, char *line);
char			*create_prompt(int amount, ...);

// HASH
int				hash_func(char *cmd, t_keyword_map *keymap);

// Process
void			exec_commands(t_sys_config *mini);
int				minishelly(int argc, char **argv, char **environ);

// Operators
int				ft_pipe(t_sys_config *mini);

// FDS
void			close_fds(t_sys_config *mini);

// EXPAND
void			expand_symbol(char **line, char c, char **env);

// Signals
void			sig_a(int sig);
void			sig_handler( int sig, siginfo_t *info, void *context);
void			wait_signal(t_sa *sa);
int				ft_ctrl_d(t_sys_config *mini);

// Frees
void			clean_exec(t_exec **exec);
void			clean_data(t_sys_config *mini);

//BUILTINS
int				ft_env(t_sys_config *mini);
int				ft_pwd(t_sys_config *mini);
int				ft_echo(t_sys_config *mini);
int				ft_cd(t_sys_config *mini);
int				ft_exit(t_sys_config *mini);
int				b_export(t_sys_config *mini);
int				b_unset(t_sys_config *mini);

// EXIT FUNCTIONS
void    normal_exit(void (*f)(void *), int exit_code, void *item);
void    sys_exit(void (*f)(t_sys_config *), int exit_code, t_sys_config *mini);


#endif