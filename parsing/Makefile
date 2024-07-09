# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hfiqar <hfiqar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 16:05:43 by hfiqar            #+#    #+#              #
#    Updated: 2024/07/08 22:48:41 by hfiqar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minicoper

SRC = tokenizer/characters.c \
	tokenizer/spaces.c \
	tokenizer/separators.c \
	tokenizer/double_quotes.c \
	tokenizer/single_quotes.c \
	tokenizer/tokenizer_utils.c \
	tokenizer/tokenizer.c \
	syntax_error/pipe.c \
	syntax_error/parser.c \
	syntax_error/num.c \
	syntax_error/cmd_args.c \
	syntax_error/new_list.c 

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
# -fsanitize=address -g
LFLAGS = "-L$(shell brew --prefix readline)/lib"
IFLAGS = "-I$(shell brew --prefix readline)/include"

OBJ = $(SRC:.c=.o)

HEADERS = tokenizer.h

all : $(NAME)

$(NAME) : $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $@ -lreadline $(LFLAGS)

%.o : %.c $(HEADERS)
	cc -c $< -o $@ $(CFLAGS)

clean:
	@$(RM) $(OBJ)
	@printf "\033[0;35mCLEANED  :|D\033[0;0m\n"

fclean:clean
	@$(RM) $(NAME)

re: fclean all

.SILENT : $(NAME) clean fclean re

.PHONY : all clean fclean re
