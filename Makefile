NAME							=						minishell

CC								=						cc
CCFLAGS							=						-Wall -Wextra -Werror
RL								=						-l readline

RM								=						rm -rf

LIBFT_PATH						=						./libft
LIBFT							=						$(LIBFT_PATH)/libft.a

SRC								=						minishell.c \
														$(addprefix utils/,  \
																			)

OBJ								=						$(SRC:%.c=%.o)

all:							$(NAME)

$(NAME):						$(OBJ)
								$(MAKE) -C $(LIBFT_PATH)
								$(CC) $(CCFLAGS) $(OBJ) $(RL) $(LIBFT) -o $(NAME)

clean:
								$(MAKE) -C $(LIBFT_PATH) clean
								$(RM) $(OBJ)

fclean:							clean
								$(MAKE) -C $(LIBFT_PATH) fclean
								$(RM) $(NAME)

re:								fclean all

.PHONY:							all clean fclean re