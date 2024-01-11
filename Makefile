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
# READLINE	= -L/usr/local/lib  -lreadline
READLINE	= -L/opt/homebrew/Cellar/readline/8.2.7/lib -lreadline

DIR			= ./
BASE		= main signal_utils \
			  parser/tk parser/tk_utils parser/mktr parser/mktr_utils \
			  parser/trtv parser/trtv_env_expand parser/trtv_word_split \
			  btin/btin_exit btin/btin_make_envsp btin/btin_cd \
			  btin/btin_echo btin/btin_env btin/btin_export \
			  btin/btin_pwd btin/btin_unset \
			  execute/ex_cmd_loop execute/ex_cmdsp execute/ex_execute execute/ex_handle_fd \
			  libft_s/libft_s_1 libft_s/ft_vector \
			  testdir/tree_print testdir/cmds_print
SRC			= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		= minishell

all : lib $(NAME)

lib :
	@make re -j -C ./libft

$(NAME) : $(OBJ)
	$(CC) -I$(dir $<) $(LIBFT) $(READLINE) $^ -o $@

# %.o : %.c
# 	$(CC) $(WFLAG) -I$(dir $<) -c $< -o $@
%.o : %.c
	$(CC) $(WFLAG) -I$(dir $<) -I/opt/homebrew/Cellar/readline/8.2.7/include -c $< -o $@

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
