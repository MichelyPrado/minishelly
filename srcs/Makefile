# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 14:03:52 by dapaulin          #+#    #+#              #
#    Updated: 2023/05/21 19:42:26 by dapaulin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Cores e emojis
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
RESET = \033[0m
ROCKET = 🚀
CLEAN = 🧹
FOLDER = 📂
ERROR = ❌

HEADERS							=						./includes/minishell.h
NAME							=						minishell

CC								=						cc
CCFLAGS							=						-Wall -Wextra -Werror
RL								=						-l readline

RM								=						rm -rf

LIBFT_PATH						=						./libft/
LIBFT							=						$(LIBFT_PATH)/libft.a

PATH_GET_SET 					=						./getters_and_setters/
GET_SET							=						$(addprefix $(PATH_GET_SET), \
														status_code.c num_pipes.c	 \
														file_descriptor.c)
PATH_TOOLS 						=						./tools/
TOOLS							=						$(addprefix $(PATH_TOOLS), \
														ft_lenfunctions.c ft_free_functions.c \
														ft_check_functions.c ft_print_msg.c \
														ft_joinfunctions.c)
PATH_SIGNALS					=						./signals/
SIGNALS							=						$(addprefix $(PATH_SIGNALS), \
														signals.c ft_ctrl_d.c)
PATH_BUILTINS					=						./builtins/
BUILTINS						=						$(addprefix $(PATH_BUILTINS), \
														cd.c echo.c env.c exit.c export.c \
														pwd.c unset.c)
PATH_ENVIRON					=						./environ/
ENVIRON							=						$(addprefix $(PATH_ENVIRON), \
														envp_utils.c handle_env.c \
														handle_path.c frees.c exit_functions.c)
PATH_HANDLE						=						./handle_input/
HANDLE							=						$(addprefix $(PATH_HANDLE), \
														ft_tokens.c handle_tokens.c \
														parser_utils.c parser.c expand.c	\
														ft_tokens_utils.c handle_operators.c \
														handle_operators_aux.c)
PATH_INTERFACES					=						./interfaces/
INTERFACES						=						$(addprefix $(PATH_INTERFACES), \
														process.c sys_config.c wait_input.c \
														minishelly.c process_init.c)
PATH_OPERATORS					=						./operators/
OPERATORS						=						$(addprefix $(PATH_OPERATORS), \
														ft_pipe.c ft_output.c ft_input.c \
														ft_append.c ft_heredoc.c)
SRC								=						minishell.c			\
														$(BUILTINS)			\
														$(ENVIRON)			\
														$(HANDLE)			\
														$(INTERFACES)		\
														$(OPERATORS)		\
														$(SIGNALS)			\
														$(TOOLS)			\
														$(GET_SET)					
OBJ								=						$(SRC:%.c=%.o)



all:							title $(LIBFT) $(NAME) complete

v: all
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --quiet ./minishell

$(OBJ): %.o: %.c $(HEADERS) 
	@$(CC)	 -g3 -fPIE $(CCFLAGS) -c $< -o $@
	@echo "$(YELLOW)$(ROCKET)  Compilando $<$(RESET)"

$(LIBFT): 
								@$(MAKE) -C $(LIBFT_PATH) --no-print-directory

$(NAME):						$(OBJ) $(HEADERS)
								@$(CC) -g3 $(CCFLAGS) $(OBJ) $(RL) $(LIBFT) $(PRINT) -o $(NAME)
	@echo	"$(GREEN)"
	@echo	'                d8,            d8,         d8b              d8b  d8b           '
	@echo	'               `8P            `8P          ?88              88P  88P           '
	@echo	'                                            88b            d88  d88            '
	@echo	'  88bd8b,d88b   88b  88bd88b   88b .d888b,  888888b  d8888b888  888  ?88   d8P '
	@echo	'  88P"`?8P"?8b  88P  88P" ?8b  88P ?8b,     88P `?8bd8b_,dP?88  ?88  d88   88  '
	@echo	' d88  d88  88P d88  d88   88P d88    `?8b  d88   88P88b     88b  88b ?8(  d88  '
	@echo	'd88" d88"  88bd88" d88"   88bd88" `?888P" d88"   88b`?888P"  88b  88b`?88P"?8b '
	@echo	'                                                                            )88'
	@echo	'                                                                           ,d8P'
	@echo	'                                                                        `?888P"'
	@echo	"$(RESET)"

clean:							title_clean 
	@							$(MAKE) -C $(LIBFT_PATH) $@ --no-print-directory
	@							$(RM) $(OBJ)
	@							echo "$(YELLOW)$(CLEAN)  Arquivos objetos removidos$(RESET)"

fclean:							clean title_fclean
	@							$(MAKE) -C $(LIBFT_PATH) $@ --no-print-directory
	@							$(RM) $(NAME)
	@							echo "$(YELLOW)$(CLEAN)  Arquivos objetos e $(NAME) removidos$(RESET)"

re:								fclean all

.PHONY:							all clean fclean re $(LIBFT)

title:
	@echo "$(GREEN)$(FOLDER)  Compilando Minishelly...$(RESET)"
	@echo "$(YELLOW)--------------------------------------$(RESET)"

title_clean:
	@echo "$(RED)$(CLEAN)  Limpando arquivos objetos...$(RESET)"
	@echo "$(YELLOW)--------------------------------------$(RESET)"

title_fclean:
	@echo "$(RED)$(CLEAN)  Limpando arquivos objetos e $(NAME)...$(RESET)"
	@echo "$(YELLOW)--------------------------------------$(RESET)"

complete:
	@echo "$(GREEN)$(ROCKET)  Minishelly compilada com sucesso!$(RESET)"
	@echo "$(YELLOW)--------------------------------------$(RESET)"
