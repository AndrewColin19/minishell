NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =  srcs/main.c srcs/ft_split.c srcs/ft_calloc.c \
		srcs/ft_parse.c

OBJS = ${SRCS:.c=.o}
all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -I includes ${OBJS} libreadline.a -lreadline -lncurses -o ${NAME}

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS}

re: fclean clean all
