CC = gcc -c

FLAGS = -Wall -Wextra -Werror

ARCHC = ar rc

NAME = libftprintf.a

LIB = ft_printf.h

SRCS = ft_printf.c ft_print_hex.c ft_print_pointer.c ft_printf_utils.c 

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIB)
		@$(CC) $(FLAGS) $(SRCS)
		@$(ARCHC) $(NAME) $(OBJS)

clean :
		@rm -rf $(OBJS)

fclean : clean
		@rm -rf $(NAME)

re : fclean all
