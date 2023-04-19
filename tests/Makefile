################  COLORS	##################
L_RED			=			\033[0;31m
L_REDB			=			\033[1;31m
L_WHITE			=			\033[0;37m
L_WHITEB		=			\033[1;37m
L_YELLOW		=			\033[0;33m
L_YELLOWB		=			\033[1;33m
L_GREEN			=			\033[0;32m
L_GREENB		=			\033[1;32m
################ CONFIG	TESTS	##################
DIR				=			../srcs/
DIR_OUTS		=			./outs/
EXEC_OUTS		=			$(wildcard $(DIR_OUTS)*)
GNL				=			$(addprefix ./get_next_line/, get_next_line.c get_next_line_utils.c)
YOUR_FILES		=			$(addprefix $(DIR), envp_utils.o handle_env.o \
												handle_path.o handle_tokens.o \
												hash.o list_token.o parser.o \
												parser_utils.o process.o \
												sys_config.o tools_box.o \
												wait_input.o) \
							$(addprefix $(DIR)builtins/, cd.o echo.o env.o \
												exit.o export.o pwd.o unset.o) \
												# Add your files with the function you can test
TESTS			=			check_readline_test \
							count_delimiter_test \
							create_prompt_test \
							edit_envp_test \
							ft_create_tokens_test \
							ft_export_test \
							ft_token_repair_test \
							ft_unset_test \
							get_envp_test \
							hash_func_test \
							list_token_test \
							search_envp_test \
							tag_token_test \
							wait_input_test \
							b_export_test \
							# Add your test names without .c
HEADERS_TEST 	= 			minunit.h
################ CONFIG YOUR PROJECT #############
FLAGS 			= 			-Wall -Werror -Wextra
################ RULES		##################
all: 		mini $(TESTS) $(EXEC_OUTS)

mini:
	@cd 		$(DIR) && $(MAKE)

$(LIBFT):
	@cd 		$(LIBFT) && $(MAKE)

$(TESTS): $(HEADERS)
	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(GNL) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)

$(EXEC_OUTS):
	@echo  "$(L_YELLOWB)$@:$(L_WHITE) " && valgrind --leak-check=full -q $@

clean:
	@rm			-f $(SRCS:.c=.o)

fclean:			clean
	@rm 		-f $(EXEC_OUTS)
	@cd 		$(DIR) && $(MAKE) $@

n:
	norminette ../srcs/

re: fclean all

.PHONY: re fclean clean all $(TESTS) $(EXEC_OUTS) $(LIBFT)

#tt: tag_token_test
#
#tag_token_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	$(DIR_OUTS)$@

#ctt: ft_create_tokens_test
#
#ft_create_tokens_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	valgrind --leak-check=full $(DIR_OUTS)$@
#
#
#ra: ft_token_repair_test
#
#ft_token_repair_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	valgrind --leak-check=full $(DIR_OUTS)$@
#
#crl: check_readline_test
#
#check_readline_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	valgrind --leak-check=full $(DIR_OUTS)$@
#
#cp: create_prompt_test
#
#create_prompt_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	valgrind --leak-check=full $(DIR_OUTS)$@

#rl: wait_input_test
#
#wait_input_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	valgrind --leak-check=full $(DIR_OUTS)$@

#h: hash_func_test
#
#hash_func_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	valgrind --leak-check=full $(DIR_OUTS)$@
#
#cd: count_delimiter_test
#
#count_delimiter_test:
#	$(CC)	-g $(addsuffix .c, $@) $(YOUR_FILES) $(DIR)libft/libft.a -o $(addprefix $(DIR_OUTS), $@)
#	valgrind --leak-check=full $(DIR_OUTS)$@