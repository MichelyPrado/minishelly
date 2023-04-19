# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dapaulin <dapaulin@student.42sp.org.br     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 22:44:13 by msilva-p          #+#    #+#              #
#    Updated: 2023/04/19 13:59:18 by dapaulin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Makefile for building libft.a library

# Cores e emojis
GREEN = \033[0;32m
YELLOW = \033[1;33m
RED = \033[0;31m
RESET = \033[0m
ROCKET = 🚀
CLEAN = 🧹
FOLDER = 📂
ERROR = ❌

# Compiler
CC		:= gcc
# Flags for C compilation
CFLAGS	:= -Wall -Wextra -Werror
# Flags for generating object files
OBJSFLAGS	:= -c
# Flags for archiving the object files into the library
ARFLAGS	:= rcs

# Directories
SRCLIB		:= ./base_functions/
SRCPRINT	:= ./ft_printf/
INCDIR		:= inc
LIBDIR		:= .

# Source files
LIB_SRCS	:= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c \
			   ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
			   ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			   ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
			   ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c \
			   ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
			   ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			   ft_strndup.c ft_islower.c ft_strcmp.c ft_uitoa.c ft_itoa_base.c
PRINTF_SRCS	:= ft_printf.c ft_printf_create.c ft_printf_formats.c \
			   ft_printf_utils.c ft_print_functions.c ft_print_flags.c \
			   flag_adm.c
UTILS_SRCS	:= functions.c

# Source files
SRCS		:= $(addprefix $(SRCLIB), $(LIB_SRCS) $(UTILS_SRCS)) $(addprefix $(SRCPRINT), $(PRINTF_SRCS))

# Object files
OBJS		:= $(addprefix $(SRCLIB), $(LIB_SRCS:.c=.o) $(UTILS_SRCS:.c=.o)) $(addprefix $(SRCPRINT), $(PRINTF_SRCS:.c=.o))

# Header files
INC		:= -I $(INCDIR)

# Library name
NAME	:= libft.a

# Regras
all: title $(NAME) complete

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS) ./includes/libft.h

$(OBJS): %.o: %.c
	@gcc -Wall -Wextra -Werror -c $< -o $@
	@echo "$(YELLOW)$(ROCKET)  Compilando $<$(RESET)"

clean: title_clean
	@$(RM) $(OBJS)
	@echo "$(YELLOW)$(CLEAN)  Arquivos objetos removidos$(RESET)"

fclean: clean title_fclean
	@$(RM) $(NAME)
	@echo "$(YELLOW)$(CLEAN)  Arquivos objetos e $(NAME) removidos$(RESET)"

re: fclean all

.PHONY: all clean fclean re

# Títulos e mensagens de processo
title:
	@echo "$(GREEN)$(FOLDER)  Compilando libft...$(RESET)"
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
