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
LIBFTF		= -Llibft -lft
READLINE	= -L/usr/local/lib -lreadline

DIR			= 
BASE		= test
SRC			= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		= minishell

all : lib $(NAME)

lib :
	@make re -j -C ./libft

$(NAME) : $(OBJ)
	$(CC) $(WFLAG) $(LIBFTFLAG) $(READLINE) $^ -o $@

%.o : %.c
	$(CC) $(WFLAG) -I $(dir $<) -c $< -o $@

clean :
	make clean -C ./libft
	rm -f $(OBJ) $(BON_OBJ) bonus

fclean : clean
	rm -f $(NAME) ./libft/libft.a

re : clean all

.PHONY : all clean fclean re

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
