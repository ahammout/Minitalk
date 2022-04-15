# Variables : Compilation tools
CC = gcc
FLAGS = -Wall -Wextra -Werror

#Variables : libraries
LIB = minitalk.h
BLIB = minitalk_bonus.h

#variables : Sources files 
SERVER = server.c 
CLIENT = client.c
LIBFTPRINTF = ft_printf/libftprintf.a
SERVERB = server_bonus.c
CLIENTB = client_bonus.c

#Variables : Objects files 
OSERVER = $(SERVER:.c=.o)
OCLIENT = $(CLIENT:.c=.o)
OBSERVER = $(SERVERB:.c=.o)
OBCLIENT = $(CLIENTB:.c=.o)

#Variables : Cleaning rule
OBJS = $(OSERVER) $(OCLIENT) $(OBSERVER) $(OBCLIENT)
EXEC = server client server_bonus client_bonus

#Mandatory part
NAME = minitalk
all : $(NAME)

$(NAME)  : $(OSERVER) $(OCLIENT) $(LIB)
	@make -C ft_printf
	@$(CC) $(FLAGS) $(SERVER) $(LIBFTPRINTF) -o server
	@$(CC) $(FLAGS) $(CLIENT) $(LIBFTPRINTF) -o client

#Bonus part
bonus : $(OBSERVER) $(OBCLIENT) $(BLIB)
	@make -C ft_printf
	@$(CC) $(FLAGS) $(SERVERB) $(LIBFTPRINTF) -o server_bonus
	@$(CC) $(FLAGS) $(CLIENTB) $(LIBFTPRINTF) -o client_bonus

#Clean objects (Mandatory + bonus)
clean :
	@make fclean -C ft_printf
	@rm -rf $(OBJS)

#Clean objects and executable files (Mandatory + Bonus)
fclean : clean
	@rm -rf $(EXEC)

#Recompile the mandatory part
re : fclean all

#Recompile the bonus part
re_bonus : fclean bonus