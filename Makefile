# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 18:58:03 by seonjo            #+#    #+#              #
#    Updated: 2024/01/05 21:09:49 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

BTIN_DIR = ./btin/
BTIN_BASE = btin_exit btin_make_envsp btin_cd\
			btin_echo btin_env btin_export\
			btin_pwd btin_unset
BTIN_SRC = $(addprefix $(BTIN_DIR), $(addsuffix .c, $(BTIN_BASE)))
BTIN_OBJ = $(addprefix $(BTIN_DIR), $(addsuffix .o, $(BTIN_BASE)))

EX_DIR = ./execute/
EX_BASE = ex_command
EX_SRC = $(addprefix $(EX_DIR), $(addsuffix .c, $(EX_BASE)))
EX_OBJ = $(addprefix $(EX_DIR), $(addsuffix .o, $(EX_BASE)))

LIBFT_S_DIR = ./libft_s/
LIBFT_S_BASE = libft_s_1
LIBFT_S_SRC = $(addprefix $(LIBFT_S_DIR), $(addsuffix .c, $(LIBFT_S_BASE)))
LIBFT_S_OBJ = $(addprefix $(LIBFT_S_DIR), $(addsuffix .o, $(LIBFT_S_BASE)))

DFT_DIR = ./
DFT_BASE = main
DFT_SRC = $(addprefix $(DFT_DIR), $(addsuffix .c, $(DFT_BASE)))
DFT_OBJ = $(addprefix $(DFT_DIR), $(addsuffix .o, $(DFT_BASE)))

OBJS = $(BTIN_OBJ) $(EX_OBJ) $(LIBFT_S_OBJ) $(DFT_OBJ)

LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -L./libft -lft -o $(NAME)

$(LIBFT) :
	@make -C ./libft

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $< -o $@

clean :
	make clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
