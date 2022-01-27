NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

SRCS =  srcs/main.c srcs/utils/ft_split.c srcs/utils/ft_calloc.c \
		srcs/ft_parse.c srcs/writter.c srcs/utils/str.c \
		srcs/utils/ft_free.c srcs/fct.c srcs/exec_cmd.c \
		srcs/check_cmd.c srcs/env.c srcs/env_expend.c \
		srcs/utils/ft_isalnum.c srcs/redirections.c \
		srcs/heredoc.c srcs/utils/ft_split_mod.c \
		srcs/del_item.c srcs/utils/ft_parse_utils.c \
		srcs/exec.c srcs/env_export.c \
		srcs/utils/ft_itoa.c srcs/fct2.c \
		srcs/utils/ft_isok.c srcs/utils/ft_tolower.c

OBJS = ${SRCS:.c=.o}
all: ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -I includes ${OBJS} libreadline.a -lreadline -lncurses -o ${NAME}

fclean: clean
	rm -f ${NAME}

clean:
	rm -f ${OBJS}

re: fclean clean all
