NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror
INC = ./mandatory/include/pipex.h
RM = rm -f

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
RESET = \033[0m

SRCS =	./mandatory/pipex.c \
		./mandatory/src/components/error_handling.c \
		./mandatory/src/components/find_command_path.c \
		./mandatory/src/components/pipex_utils.c \
		./mandatory/src/lib/ft_split.c \
		./mandatory/src/lib/ft_strdup.c \
		./mandatory/src/lib/ft_strjoin.c \
		./mandatory/src/lib/ft_strlen.c \
		./mandatory/src/lib/ft_strncmp.c \
		./mandatory/src/lib/ft_strtok.c \

OBJS = $(SRCS:.c=.o)

mandatory/%.o: mandatory/%.c ${INC}
	@printf "$(YELLOW)Compiling: $<$(RSEST)\n"
	@${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJS}
	@printf "$(GREEN)Building: ${NAME}$(RESET)\n"
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

all: ${NAME}

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) $(OBJS)

fclean: clean
	@printf "$(RED)Removing executable...$(RESET)\n"
	@$(RM) ${NAME}

re: fclean all

.PHONY: all clean fclean re