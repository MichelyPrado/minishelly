#ifndef TESTS_INCLUDES_H
# define TESTS_INCLUDES_H
#include "../../srcs/includes/minishell.h"
#include "../get_next_line/get_next_line.h"
#include "../minunit-42/minunit.h"

# define PIPE_T     &((t_token){.token = (char *[]){"|", NULL}, .type = OP_PIPE, .next = NULL})
# define CAT_T      &((t_token){.token = (char *[]){"/usr/bin/cat", "./testes_files/vinculo.txt", NULL}, .type = OP_CMD, .next = NULL})
# define GREP_T     &((t_token){.token = (char *[]){"/usr/bin/grep", "galo", NULL}, .type = OP_CMD, .next = NULL})
# define WC_T       &((t_token){.token = (char *[]){"/usr/bin/wc", "-c", NULL}, .type = OP_CMD, .next = NULL})
# define TR_T       &((t_token){.token = (char *[]){"/usr/bin/tr", "5", "2", NULL}, .type = OP_CMD, .next = NULL})
# define ECHO_T     &((t_token){.token = (char *[]){"echo", "taca lhe pau no carrinho marcos!", NULL}, .type = OP_ECHO, .next = NULL})
# define EXIT_T     &((t_token){.token = (char *[]){"exit", NULL}, .type = OP_EXIT, .next = NULL})
# define CD_T       &((t_token){.token = (char *[]){"cd", NULL}, .type = OP_CD, .next = NULL})
# define ENV_T      &((t_token){.token = (char *[]){"env", NULL}, .type = OP_ENV, .next = NULL})
# define PWD_T      &((t_token){.token = (char *[]){"pwd", NULL}, .type = OP_PWD, .next = NULL})
# define EXPORT_T   &((t_token){.token = (char *[]){"export", "PL=vida", NULL}, .type = OP_EXPORT, .next = NULL})
# define UNSET_T    &((t_token){.token = (char *[]){"unset", "PWD", NULL}, .type = OP_UNSET, .next = NULL})
# define OUT_T      &((t_token){.token = (char *[]){">", "./testes_files/google.tx", NULL}, .type = OP_OUTPUT, .next = NULL})
# define CMD_T(CMD, OP)      &((t_token){.token = (char *[])CMD, .type = OP, .next = NULL})

# define OUT_M      ft_token_new(ft_split("> ./testes_files/google.tx", 32), OP_OUTPUT)
# define ECHO_M     ft_token_new(ft_split("echo\ataca lhe pau no carrinho marcos!", '\a'), OP_ECHO)
# define CMD_M(CMD, C, OP)      ft_token_new(ft_split(CMD, C), OP)

int g_fd;

#endif