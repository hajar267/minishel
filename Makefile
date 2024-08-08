# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: istili <istili@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 16:05:43 by hfiqar            #+#    #+#              #
#    Updated: 2024/08/08 00:16:40 by istili           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = parsing/tokenizer/characters.c \
	parsing/tokenizer/spaces.c \
	parsing/tokenizer/separators.c \
	parsing/tokenizer/double_quotes.c \
	parsing/tokenizer/single_quotes.c \
	parsing/tokenizer/tokenizer_utils.c \
	parsing/tokenizer/tokenizer.c \
	parsing/syntax_error/error.c \
	parsing/syntax_error/cmd_args.c \
	parsing/expander/expander_utils.c \
	parsing/expander/heredoc.c \
	parsing/expander/heredoc_expander_helper.c \
	parsing/expander/heredoc_expander.c \
	parsing/final_list/new_list.c \
	parsing/final_list/enum.c \
	parsing/final_list/open_files.c \
	parsing/final_list/store_data.c \
	utils/gab.c \
	utils/signals.c \
	environment/env_linked.c \
	environment/ft_itoa.c \
	environment/functions.c \
	environment/libc.c \
	environment/make_my_own_env.c \
	environment/ft_split.c \
	builtins/cd_helpers.c \
	builtins/cd.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/export_helper.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/pwd.c \
	builtins/unset.c \
	execution/execution.c  execution/helpers.c execution/path.c execution/pipex.c \
	main_exec.c \
	main.c \

CFLAGS = -Wall -Wextra -Werror -ggdb3

LFLAGS = -L$(shell brew --prefix readline)/lib

IFLAGS = -I$(shell brew --prefix readline)/include

OBJ = $(SRC:.c=.o)

HEADER_FILE = minishell.h

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $@ -lreadline $(LFLAGS)

%.o : %.c $(HEADER_FILE)
	cc -c $< -o $@ $(CFLAGS) $(IFLAGS)

clean:
	@$(RM) $(OBJ)
	@printf "\033[0;35mCLEANED  :|D\033[0;0m\n"

fclean:clean
	@$(RM) $(NAME)

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY : all clean fclean re
