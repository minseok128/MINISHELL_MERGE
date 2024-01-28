# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/01 21:01:14 by michang           #+#    #+#              #
#    Updated: 2024/01/25 16:06:04 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			= cc
WFLAG		= -Wall -Wextra -Werror
LIBFT		= -Llibft -lft
READLINE	= -L/usr/local/lib -lreadline

DIR			= ./src/
BASE		= main signal parser/parser_set \
			  parser/tk parser/tk_utils parser/mktr parser/mktr_utils parser/mktr_heredoc\
			  parser/trtv parser/trtv_env_expand parser/trtv_wsplit parser/trtv_redir\
			  parser/trtv_utils \
			  btin/btin_exit btin/btin_make_envsp btin/btin_cd \
			  btin/btin_echo btin/btin_env btin/btin_export \
			  btin/btin_pwd btin/btin_unset btin/btin_make_errmsg \
			  btin/btin_export_utils \
			  execute/ex_cmdsp execute/ex_cmd_loop execute/ex_execute \
			  execute/ex_handle_fd execute/ex_btin_execute execute/ex_execute_utils \
			  libft_s/libft_s_1 libft_s/libft_s_2 libft_s/ft_vector
SRC			= $(addprefix $(DIR), $(addsuffix .c, $(BASE)))
OBJ			= $(addprefix $(DIR), $(addsuffix .o, $(BASE)))
NAME		= minishell

BON_DIR		= ./bon/
BON_BASE	= main signal parser/parser_set \
			  parser/tk parser/tk_utils parser/mktr parser/mktr_utils parser/mktr_heredoc\
			  parser/trtv parser/trtv_env_expand parser/trtv_wsplit parser/trtv_redir\
			  parser/trtv_wcard parser/trtv_utils \
			  btin/btin_exit btin/btin_make_envsp btin/btin_cd \
			  btin/btin_echo btin/btin_env btin/btin_export \
			  btin/btin_pwd btin/btin_unset btin/btin_make_errmsg \
			  btin/btin_export_utils \
			  execute/ex_cmdsp execute/ex_cmd_loop execute/ex_execute \
			  execute/ex_handle_fd execute/ex_btin_execute execute/ex_execute_utils \
			  libft_s/libft_s_1 libft_s/libft_s_2 libft_s/ft_vector
BON_SRC		= $(addprefix $(BON_DIR), $(addsuffix _bonus.c, $(BON_BASE)))
BON_OBJ		= $(addprefix $(BON_DIR), $(addsuffix _bonus.o, $(BON_BASE)))
BON_NAME	= minishell

all : $(NAME)

$(NAME) : $(OBJ)
	@make lib
	$(CC) -I$(dir $<) $(LIBFT) $(READLINE) $^ -o $@

bonus : $(BON_OBJ)
	@make lib
	$(CC) -I$(dir $<) $(LIBFT) $(READLINE) $^ -o $(BON_NAME)
	@touch bonus

%.o : %.c
	$(CC) $(WFLAG) -I$(dir $<) -c $< -o $@

lib :
	@make re -j -C ./libft

clean :
	make clean -C ./libft
	rm -f $(OBJ) $(BON_OBJ) bonus

fclean : clean
	rm -f $(NAME) $(BON_NAME) ./libft/libft.a

re : clean all

.PHONY : all clean fclean re
