NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRCS =  srcs/main.c srcs/utils/ft_split.c srcs/utils/ft_calloc.c \
		srcs/ft_parse.c srcs/writter.c srcs/utils/str.c \
		srcs/utils/ft_free.c srcs/fct.c srcs/exec_cmd.c \
		srcs/check_cmd.c srcs/env.c srcs/env_expend.c \
		srcs/utils/ft_isalnum.c srcs/redirections.c \
		srcs/heredoc.c

OBJS = ${SRCS:.c=.o}
all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -I includes ${OBJS} libreadline.a -lreadline -lncurses -o ${NAME}

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS}

re: fclean clean all
