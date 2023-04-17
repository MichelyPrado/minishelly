################  COLORS	##################
L_RED			=			\033[0;31m
L_REDB			=			\033[1;31m
L_WHITE			=			\033[0;37m
L_WHITEB		=			\033[1;37m
L_YELLOW		=			\033[0;33m
L_YELLOWB		=			\033[1;33m
L_GREEN			=			\033[0;32m
L_GREENB		=			\033[1;32m

NAME							=						minishell

CC								=						cc
CCFLAGS							=						-Wall -Wextra -Werror
RL								=						-l readline

RM								=						rm -rf

LIBFT_PATH						=						./libft
LIBFT							=						$(LIBFT_PATH)/libft.a
PATH_BUILTINS					=						./builtins/
BUILTINS						=						$(addprefix $(PATH_BUILTINS), \
														cd.c echo.c env.c exit.c export.c \
														pwd.c unset.c)
SRC								=						minishell.c			\
														handle_env.c		\
														envp_utils.c		\
														handle_path.c		\
														parser.c			\
														tools_box.c			\
														parser_utils.c		\
														list_token.c		\
														handle_tokens.c		\
														wait_input.c		\
														sys_config.c		\
														hash.c				\
														process.c			\
														$(BUILTINS)			
OBJ								=						$(SRC:%.c=%.o)


all:							$(LIBFT) $(NAME) 


%.o: %.c $(HEADERS)
	$(CC)	 $(CCFLAGS) -c $< -o $@

$(LIBFT):
								$(MAKE) -C $(LIBFT_PATH)

$(NAME):						$(OBJ)
								$(CC) -g3 $(CCFLAGS) $(OBJ) $(RL) $(LIBFT) -o $(NAME)
	@echo	"$(L_GREENB)"
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
	@echo	"$(L_WHITE)"

clean:
								$(MAKE) -C $(LIBFT_PATH) clean
								$(RM) $(OBJ)

fclean:							clean
								$(MAKE) -C $(LIBFT_PATH) fclean
								$(RM) $(NAME)

re:								fclean all

.PHONY:							all clean fclean re