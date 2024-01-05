# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 18:58:03 by seonjo            #+#    #+#              #
#    Updated: 2024/01/05 16:41:10 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror

BTIN_DIR = ./builtin/
BTIN_BASE = builtin_exit builtin_make_envsp builtin_cd\
			builtin_echo builtin_env builtin_export\
			builtin_pwd builtin_unset
BTIN_SRC = $(addprefix $(BTIN_DIR), $(addsuffix .c, $(BTIN_BASE)))
BTIN_OBJ = $(addprefix $(BTIN_DIR), $(addsuffix .o, $(BTIN_BASE)))

DFT_DIR = ./
DFT_BASE = main command
DFT_SRC = $(addprefix $(DFT_DIR), $(addsuffix .c, $(DFT_BASE)))
DFT_OBJ = $(addprefix $(DFT_DIR), $(addsuffix .o, $(DFT_BASE)))

LIBFT_S_DIR = ./libft_s/
LIBFT_S_BASE = libft_s_1
LIBFT_S_SRC = $(addprefix $(LIBFT_S_DIR), $(addsuffix .c, $(LIBFT_S_BASE)))
LIBFT_S_OBJ = $(addprefix $(LIBFT_S_DIR), $(addsuffix .o, $(LIBFT_S_BASE)))

OBJS = $(BTIN_OBJ) $(DFT_OBJ) $(LIBFT_S_OBJ)

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
