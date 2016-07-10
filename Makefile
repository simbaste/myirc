##
## Makefile for myirc in /home/simomb_s/semestre4/rendu_4/PSU_2015_myirc
##
## Made by stephanedarcy simomba
## Login   <simomb_s@epitech.net>
##
## Started on  Mon May 16 09:06:18 2016 stephanedarcy simomba
## Last update Sun Jun  5 19:02:48 2016 nicolas thouchkaieff
##

CC	= gcc

PATH_S	= src/server

PATH_C	= src/client

PATH_F	= src/function

NAME_S	= server

NAME_C	= client

CFLAGS	+= -W -Wall -Werror -Wextra
CFLAGS	+= -Iinclude

SRCS_S	= $(PATH_S)/main.c	\
	$(PATH_F)/list_chanel.c	\
	$(PATH_F)/list_client.c	\
	$(PATH_F)/func.c	\
	$(PATH_S)/f_msg.c	\
	$(PATH_S)/f_nick.c	\
	$(PATH_S)/f_list.c	\
	$(PATH_S)/f_names.c	\
	$(PATH_S)/f_join.c	\
	$(PATH_S)/f_part.c	\
	$(PATH_S)/my_gets.c	\
	$(PATH_S)/init.c	\
	$(PATH_S)/server.c	\
	$(PATH_S)/ring_buff.c	\

SRCS_C	= $(PATH_C)/main.c	\
	$(PATH_F)/list_chanel.c	\
	$(PATH_F)/func.c	\
	$(PATH_C)/f_cmds.c	\
	$(PATH_C)/f_server.c	\
	$(PATH_C)/f_quit.c	\
	$(PATH_C)/read_serv.c	\
	$(PATH_C)/client.c	\
	$(PATH_C)/first_connect.c \

OBJS_S	= $(SRCS_S:.c=.o)

OBJS_C	= $(SRCS_C:.c=.o)

RM	= rm -f
PRINTF	= @printf

all: $(NAME_S) $(NAME_C)

$(NAME_S) : $(OBJS_S)
	$(CC) $(OBJS_S) -o $(NAME_S)
	$(PRINTF) '\033[1;32m> Compiled\033[0m\n'

$(NAME_C) : $(OBJS_C)
	$(CC) $(OBJS_C) -o $(NAME_C)
	$(PRINTF) '\033[1;32m> Compiled\033[0m\n'

clean:
	$(RM) $(OBJS_S)
	$(RM) $(OBJS_C)
	$(PRINTF) '\033[1;35m> Directory cleaned\033[0m\n'

fclean: clean
	$(RM) $(NAME_S)
	$(RM) $(NAME_C)
	$(PRINTF) '\033[1;35m> Remove executable\033[0m\n'

re: fclean all

.PHONY: all clean fclean re
