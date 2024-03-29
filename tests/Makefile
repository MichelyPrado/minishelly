################  COLORS	##################
L_RED			=			\033[0;31m
L_REDB			=			\033[1;31m
L_WHITE			=			\033[0;37m
L_WHITEB		=			\033[1;37m
L_YELLOW		=			\033[0;33m
L_YELLOWB		=			\033[1;33m
L_GREEN			=			\033[0;32m
L_GREENB		=			\033[1;32m
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
RESET = \033[0m
ROCKET = 🚀
CLEAN = 🧹
FOLDER = 📂
ERROR = ❌
################ CONFIG	TESTS	##################
DIR										=				../srcs/
DIR_OUTS								=				./outs/
EXEC_OUTS								=				$(wildcard $(DIR_OUTS)*)
GNL										=				$(addprefix ./get_next_line/, get_next_line.c get_next_line_utils.c)
FILES									=				../srcs
DIR_BUILTINS							=				/builtins/
DIR_ENVIRON								=				/environ/
DIR_HANDLE								=				/handle_input/
DIR_INTERFACES							=				/interfaces/
DIR_OPERATORS							=				/operators/
DIR_SIGNALS								=				/signals/
DIR_TOOLS								=				/tools/
DIR_GET_SET								=				/getters_and_setters/
DIR_LIBFT								=				/libft/
YOUR_FILES								=				$(wildcard $(FILES)$(DIR_BUILTINS)*.c)						\
														$(wildcard $(FILES)$(DIR_TOOLS)*.c)							\
														$(wildcard $(FILES)$(DIR_GET_SET)*.c)							\
														$(wildcard $(FILES)$(DIR_SIGNALS)*.c)						\
														$(wildcard $(FILES)$(DIR_ENVIRON)*.c)						\
														$(wildcard $(FILES)$(DIR_HANDLE)*.c)						\
														$(wildcard $(FILES)$(DIR_OPERATORS)*.c)						\
														$(addprefix $(FILES)$(DIR_INTERFACES),						\
														process.c sys_config.c wait_input.c 						\
														process_init.c dup_functions.c)
OBJS_FILES								=				$(YOUR_FILES:%.c=%.o)										\
														$(addprefix $(FILES)$(DIR_LIBFT), libft.a)					\
														# Add your files with the function you can test
TPATH_TOOLS							=					tools_tests/
TESTS_TOOLS							=					$(addprefix $(TPATH_TOOLS), 								\
														ft_listjoin_test)
TPATH_BUILTINS							=				builtins_tests/
TESTS_BUILTINS							=				$(addprefix $(TPATH_BUILTINS), 								\
														b_export_test ft_cd_test ) \
														# ft_pwd_test
TPATH_OPERATORS							=				operators_tests/
TESTS_OPERATORS							=				$(addprefix $(TPATH_OPERATORS),			 				\
														ft_output_test)
TPATH_ENVIRON							=				environ_tests/
TESTS_ENVIRON							=				$(addprefix $(TPATH_ENVIRON), 								\
														search_envp_test			edit_envp_test	 				\
														get_envp_test 				ft_unset_test 					\
														ft_export_test 				cmd_path_valid_test)
TPATH_INTERFACES						=				interfaces_tests/
TESTS_INTERFACES						=				$(addprefix $(TPATH_INTERFACES),			 				\
														wait_input_test 			create_prompt_test				\
														)#exec_test
TPATH_HANDLE							=				handle_input_tests/
#														handle_tokens_test
TESTS_HANDLE							=				$(addprefix $(TPATH_HANDLE), 								\
														check_readline_test 		 								\
														tag_token_test 				ft_token_repair_test 			\
														ft_create_tokens_test 		list_token_test					\
														hash_func_test 				count_delimiter_test			\
														expand_test 				ft_swap_token_test	 			\
														ft_handle_files_test)										\
														# ft_tokens_swap_test \
														# Add your test names without .c
TESTS									=				$(TESTS_BUILTINS)											\
														$(TESTS_ENVIRON)											\
														$(TESTS_HANDLE)												\
														$(TESTS_INTERFACES)											\
														$(TESTS_OPERATORS)											\
														$(TESTS_TOOLS)
EXEC_OUTS								=				$(addprefix $(DIR_OUTS), $(TESTS))										
################ CONFIG YOUR PROJECT #############
FLAGS 									=	 			-Wall -Werror -Wextra
################ RULES		##################
all: 		mini $(TESTS) $(EXEC_OUTS)

mini:
	@cd 		$(DIR) && $(MAKE) --no-print-directory

$(TESTS): $(HEADERS)
	@			$(CC)	-g $(OBJS_FILES) -l readline $(GNL) $@.c -o $(addprefix $(DIR_OUTS), $@)
	@			echo "$(YELLOW)$(ROCKET)  Compilando $@$(RESET)"

$(EXEC_OUTS):
	@			echo "           "
	@			echo  "$(L_YELLOWB)$@:$(L_WHITE) " && valgrind --leak-check=full -q $@

clean:			title_clean
	@			$(MAKE) -C $(DIR) $@ --no-print-directory
	@			$(RM) $(OBJS_FILES)
	@			echo "$(YELLOW)$(CLEAN)  Arquivos objetos removidos$(RESET)"

fclean:			clean title_fclean
	@			$(MAKE) -C $(DIR) $@ --no-print-directory
	@			$(RM) $(EXEC_OUTS)
	@			echo "$(YELLOW)$(CLEAN)  Arquivos objetos e $(NAME) removidos$(RESET)"

n:
	norminette ../srcs/

# Compila os arquivos da minishelly
build-objs: $(HEADERS)
	@cd 		$(DIR) && $(MAKE) --no-print-directory

# Usando para rodar tests unicos
# formato de uso
# make run-test TEST_NAME=<dir><file-test>
# make run-test TEST_NAME=./environ_tests/ft_is_cmd_test
run-test: build-objs
	@			$(CC) -g $(OBJS_FILES) -l readline $(GNL) $(TEST_NAME).c -o $(addprefix $(DIR_OUTS), $(TEST_NAME))
	@			echo "$(YELLOW)$(ROCKET)  Executando teste $(TEST_NAME)$(RESET)"
	@			valgrind --leak-check=full --show-leak-kinds=all -q $(addprefix $(DIR_OUTS), $(TEST_NAME))
#	@			$(addprefix $(DIR_OUTS), $(TEST_NAME))
#	@			gdb --tui $(addprefix $(DIR_OUTS), $(TEST_NAME))

re: fclean all

.PHONY: re fclean clean all $(TESTS) $(EXEC_OUTS) $(LIBFT)

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
	@echo "$(GREEN)$(ROCKET)  libft compilada com sucesso!$(RESET)"
	@echo "$(YELLOW)--------------------------------------$(RESET)"