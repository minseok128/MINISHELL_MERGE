CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_strncmp.c ft_tolower.c ft_toupper.c ft_strchr.c \
	ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_putnbr_fd.c
SRCS2 = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
	ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS = $(SRCS:.c=.o)
OBJECTS2 = $(SRCS2:.c=.o)
ARRCS = ar rcus
INC = -I./
RMF = rm -f

all : $(NAME)

bonus : $(OBJECTS2) $(NAME)
	$(ARRCS) $(NAME) $(OBJECTS2)
	@touch bonus

$(NAME) : $(OBJECTS)
	@$(ARRCS) $(NAME) $(OBJECTS)
	@echo "\033[32;1m"libft.a is created"\033[m"

%.o : %.c
	@$(CC) $(CFLAGS) -c $(INC) $<

clean :
	@$(RMF) $(OBJECTS) $(OBJECTS2) bonus

fclean : clean
	@$(RMF) $(NAME)

re :
	@make fclean
	@make all

.PHONY : all clean fclean re