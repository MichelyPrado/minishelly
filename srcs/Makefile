NAME							=						minishell

CC								=						cc
CCFLAGS							=						-Wall -Wextra -Werror
RL								=						-l readline

RM								=						rm -rf

LIBFT_PATH						=						./libft
LIBFT							=						$(LIBFT_PATH)/libft.a

SRC								=						minishell.c			\
														handle_env.c		\
														envp_utils.c		\
														handle_path.c
OBJ								=						$(SRC:%.c=%.o)

all:							$(LIBFT) $(NAME)

%.o: %.c $(HEADERS)
	$(CC)	 $(CCFLAGS) -c $< -o $@

$(LIBFT):
								$(MAKE) -C $(LIBFT_PATH)

$(NAME):						$(OBJ)
								$(CC) $(CCFLAGS) $(OBJ) $(RL) $(LIBFT) -o $(NAME)

clean:
								$(MAKE) -C $(LIBFT_PATH) clean
								$(RM) $(OBJ)

fclean:							clean
								$(MAKE) -C $(LIBFT_PATH) fclean
								$(RM) $(NAME)

re:								fclean all

.PHONY:							all clean fclean re