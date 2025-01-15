NAME = pipex
NAMEB = pipexl
CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address -g
INC = ./mandatory/include/pipex.h
INCB = ./bonus/include/pipex.h
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

SRCSB =	./bonus/pipex.c \
		./bonus/src/components/error_handling.c \
		./bonus/src/components/find_command_path.c \
		./bonus/src/components/pipex_utils.c \
		./bonus/src/lib/ft_split.c \
		./bonus/src/lib/ft_strdup.c \
		./bonus/src/lib/ft_strjoin.c \
		./bonus/src/lib/ft_strlen.c \
		./bonus/src/lib/ft_strncmp.c \
		./bonus/src/lib/ft_strtok.c \
		./bonus/get_next_line/get_next_line.c \
		./bonus/get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)
OBJSB = $(SRCSB:.c=.o)

mandatory/%.o: mandatory/%.c ${INC}
	@printf "$(YELLOW)Compiling: $<$(RSEST)\n"
	@${CC} ${FLAGS} -c $< -o $@

bonus/%.o: bonus/%.c ${INCB}
	@printf "$(YELLOW)Compiling: $<$(RSEST)\n"
	${CC} ${FLAGS} -c $< -o $@

${NAME}: ${OBJS}
	@printf "$(GREEN)Building: ${NAME}$(RESET)\n"
	${CC} ${FLAGS} ${OBJS} -o ${NAME}

${NAMEB}: ${OBJSB}
	@printf "$(GREEN)Building: ${NAMEB}$(RESET)\n"
	${CC} ${FLAGS} ${OBJSB} -o ${NAMEB}

all: ${NAME} ${NAMEB}

bonus: ${NAMEB}

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) $(OBJS) $(OBJSB)

fclean: clean
	@printf "$(RED)Removing executable...$(RESET)\n"
	@$(RM) ${NAME} ${NAMEB}

re: fclean all

.PHONY: all bonus clean fclean re
