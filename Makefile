NAME	= server

CC	= gcc

RM	= rm -f

SRCS	=	./src/commands/cmd_cdup.c \
		./src/commands/cmd_cwd.c \
		./src/commands/cmd_dele.c \
		./src/commands/cmd_help.c \
		./src/commands/cmd_list.c \
		./src/commands/cmd_noop.c \
		./src/commands/cmd_pass.c \
		./src/commands/cmd_pasv.c \
		./src/commands/cmd_port.c \
		./src/commands/cmd_pwd.c \
		./src/commands/cmd_quit.c \
		./src/commands/cmd_retr.c \
		./src/commands/cmd_stor.c \
		./src/commands/cmd_user.c \
		./src/commands/cmd_type.c \
		./src/commands/cmd_feat.c \
		./src/commands/cmd_size.c \
		./src/network.c	\
		./src/data.c	\
		./src/command.c	\
		./src/path_handler.c	\
		./src/regex.c	\
		./src/myftp.c \
		./src/server.c \
		./src/socket.c

OBJS	= $(SRCS:.c=.o)

CFLAGS = -I ./include/
CFLAGS += -W -Wall -Wextra

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
