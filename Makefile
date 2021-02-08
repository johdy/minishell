# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/08 11:43:36 by jdyer             #+#    #+#              #
#    Updated: 2021/02/08 11:43:38 by jdyer            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

SRCS = srcs/build_commands/get_commands.c	\
	srcs/build_commands/get_quotes_stickits_infos.c	\
	srcs/build_lex/deal_special.c	\
	srcs/build_lex/get_lex.c	\
	srcs/builtins/ft_cd.c	\
	srcs/builtins/ft_env_unset.c	\
	srcs/builtins/ft_export.c	\
	srcs/builtins/ft_export_utils.c	\
	srcs/builtins/other_builtns.c	\
	srcs/clean/clean.c	\
	srcs/clean/ft_failed.c	\
	srcs/correct_commands/correct_commands.c	\
	srcs/correct_commands/deal_dollars.c	\
	srcs/correct_commands/first_cmd_crct.c	\
	srcs/correct_commands/sticking.c	\
	srcs/execution_and_redirections/execution.c	\
	srcs/execution_and_redirections/execution_utils.c	\
	srcs/execution_and_redirections/redirection.c	\
	srcs/get_bin_path_environ/ft_split_path.c	\
	srcs/get_bin_path_environ/get_bin_and_path.c	\
	srcs/get_bin_path_environ/init_env.c	\
	srcs/signals/ctrl_d.c	\
	srcs/signals/signals_handling.c	\
	srcs/utils/char_utils.c	\
	srcs/utils/cmd_utils.c	\
	srcs/utils/env_fd_util.c	\
	srcs/utils/ft_strcmp.c	\
	srcs/utils/get_next_line.c	\
	srcs/utils/get_next_line_utils.c	\
	srcs/utils/list_utils.c	\
	srcs/minishell.c

OBJS = $(SRCS:.c=.o)

INCLUDES = inc/ 

LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

all: makelibft $(NAME)

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(LIBFT)

makelibft :
	cd $(LIBFTDIR) && make && make bonus && cd ..

%.o: %.c $(INCLUDES)
	$(CC) -c -I$(INCLUDES) -I$(LIBFTDIR) -o $@ $<

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFTDIR)

fclean:	clean
	rm -rf $(NAME)
	make fclean -C $(LIBFTDIR)

re: fclean all

.PHONY: 		all fclean clean re
