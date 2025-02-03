# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 01:22:50 by oloncle           #+#    #+#              #
#    Updated: 2025/01/31 11:22:30 by oloncle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

#Directories and srcs
NAME = minishell

LEX_SRCS = lexer.c\
	    handle_quotes.c\
	    handle_quotes_2.c\
	    identifying_tok_1.c\
	    identifying_tok_2.c\
	    lexer_utils.c\

PARS_SRCS = libft_utils.c\
	    creating_ast.c\
	    ft_split_mod.c\
	    creating_cmd_nodes.c\
	    creating_pipe_nodes.c\

SRC_FILES = main.c\

SRC_DIR = ./src/

PARS_DIR = ./src/parsing/

LEX_DIR = ./src/parsing/lexing/

CFILES = $(addprefix $(SRC_DIR), $(SRC_FILES)) $(addprefix $(LEX_DIR), $(LEX_SRCS)) $(addprefix $(PARS_DIR), $(PARS_SRCS))

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

$(NAME): $(patsubst %.c, %.o, $(CFILES))
	$(CC) $(CFLAGS) $? -lreadline -o $(NAME)

clean:
	rm -f $(SRC_DIR)*.o
	rm -f $(PARS_DIR)*.o
	rm -f $(LEX_DIR)*.o

fclean: clean
	rm -f $(NAME)

re: fclean all