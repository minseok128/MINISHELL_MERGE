# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: michang <michang@student.42seoul.k>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 21:01:14 by michang           #+#    #+#              #
#    Updated: 2023/09/01 21:01:15 by michang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
WFLAG		= -Wall -Wextra -Werror
LIBFT		= -Llibft -lft
READLINE	= -L/usr/local/lib  -lreadline
# READLINE	= -L/opt/homebrew/Cellar/readline/8.2.7/lib -lreadline

DIR			= ./
BASE		= main signal_utils env env_init parser/tk parser/tk_utils
SRC			= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		= minishell

all : lib $(NAME)

lib :
	@make re -j -C ./libft

$(NAME) : $(OBJ)
	$(CC) $(WFLAG) -I$(dir $<) $(LIBFT) $(READLINE) $^ -o $@

%.o : %.c
	$(CC) $(WFLAG) -I$(dir $<) -c $< -o $@
# %.o : %.c
# 	$(CC) $(WFLAG) -I$(dir $<) -I/opt/homebrew/Cellar/readline/8.2.7/include -c $< -o $@

clean :
	make clean -C ./libft
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) ./libft/libft.a

re : clean all

.PHONY : all clean fclean re

t : all clean
	./$(NAME)

party :
	@printf "\033c"
	@echo "\n\033[35m♪┏(・o･)┛♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[1;33m♪┗(・o･)┓♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[36m♪┏(・o･)┛♪\n"
	@sleep 0.5
	@printf "\033c"
	@echo "\n\033[34m♪┗(・o･)┓♪\n"
	@clear
