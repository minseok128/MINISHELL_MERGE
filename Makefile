# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 18:58:03 by seonjo            #+#    #+#              #
#    Updated: 2024/01/04 18:57:41 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c command.c builtin_btin_make_envsp.c btin_cd.c btin_echo.c btin_env.c btin_export.c btin_pwd.c btin_unset.c wrap_libft.c
OBJS = $(SRCS:.c=.o)
LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(FLAGS) $(OBJS) -L./libft -lft -o $(NAME)

$(LIBFT) :
	@make -C ./libft

%.o : %.c
	$(CC) $(CFLAGS) -I . -c $<

clean :
	make clean -C ./libft
	rm -f $(OBJS)

fclean : clean
	make fclean -C ./libft
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
