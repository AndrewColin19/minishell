NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS =  srcs/main.c srcs/utils/ft_split.c srcs/utils/ft_calloc.c \
		srcs/ft_parse.c srcs/writter.c srcs/utils/str.c \
		srcs/utils/ft_free.c srcs/fct.c

OBJS = ${SRCS:.c=.o}
all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -I includes ${OBJS} libreadline.a -lreadline -lncurses -o ${NAME}

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS}

re: fclean clean all
