NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror
INC = ./mandatory/include/pipex..h
RM = rm -f

SRCS =	./mandatory/pipex.c \
		./mandatory/src/components/error_handling.c \
		./mandatory/src/components/find_command_path.c \
		./mandatory/src/components/pipex_utils.c \
		./mandatory/src/lib/ft_split.c \
		./mandatory/src/lib/ft_strjoin.c \
		./mandatory/src/lib/ft_strlen.c \

OBJS = $(SRCS:.c=.o)

mandatory/%.o: mandatory/%.c ${INC}
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o ${NAME}


all: ${NAME}

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re