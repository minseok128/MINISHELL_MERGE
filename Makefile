# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seonjo <seonjo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/08 18:58:03 by seonjo            #+#    #+#              #
#    Updated: 2023/12/21 18:57:23 by seonjo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS = main.c built_in_cd.c built_in_echo.c built_in_env_list.c built_in_env.c built_in_export.c built_in_pwd.c built_in_unset.c tree_execute.c tree_preorder_fd_list.c tree_preorder.c tree_redirection.c
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
