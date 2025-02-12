# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oloncle <oloncle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/15 01:22:50 by oloncle           #+#    #+#              #
#    Updated: 2025/02/12 17:14:20 by oloncle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

#Directories and srcs
NAME = minishell

EXEC_SRCS = cd.c\
	    do_cmd.c\
	    echo.c\
	    env.c\
	    exec.c\
	    exit.c\
	    export.c\
	    init_path.c\
	    norme.c\
	    path_utils.c\
	    pwd.c\
	    unset.c\
	    ft_strjoin.c\
	    ft_strchr.c\
	    ft_isalpha.c\
	    ft_isalnum.c\

LEX_SRCS = lexer.c\
	    handle_quotes.c\
	    handle_quotes_2.c\
	    identifying_tok_1.c\
	    identifying_tok_2.c\
	    heredoc_handling.c\
	    heredoc_utils_1.c\
	    heredoc_utils_2.c\
	    lexer_utils.c\
	    ft_itoa.c\
	    var_env_handler.c\

PARS_SRCS = libft_utils.c\
	    creating_ast.c\
	    ft_split_mod.c\
	    creating_cmd_nodes.c\
	    creating_pipe_nodes.c\
	    free_pars.c\
	    creating_tab_env.c\
	    parsing_utils.c\

MAIN_FILES = main.c\
	     signals_handler.c\
	     prompting.c\
	     debugging_print.c\

MAIN_DIR = ./src/main/

PARS_DIR = ./src/parsing/

LEX_DIR = ./src/parsing/lexing/

EXEC_DIR = ./src/exec/

CFILES = $(addprefix $(MAIN_DIR), $(MAIN_FILES)) $(addprefix $(LEX_DIR), $(LEX_SRCS)) $(addprefix $(PARS_DIR), $(PARS_SRCS)) $(addprefix $(EXEC_DIR), $(EXEC_SRCS))

CFLAGS = -Wall -Werror -Wextra -g

CC = cc

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@

$(NAME): $(patsubst %.c, %.o, $(CFILES))
	$(CC) $(CFLAGS) $? -lreadline -o $(NAME)

clean:
	rm -f $(MAIN_DIR)*.o
	rm -f $(PARS_DIR)*.o
	rm -f $(LEX_DIR)*.o
	rm -f $(EXEC_DIR)*.o

fclean: clean
	rm -f $(NAME)

re: fclean all