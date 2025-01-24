NAME = pipex
NAMEB = pipex_bonus
CC = cc
FLAGS = -Wall -Wextra -Werror
INC = ./mandatory/include/pipex.h
INCB = ./bonus/include/pipex_bonus.h
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

SRCSB =	./bonus/pipex_bonus.c \
		./bonus/src/components/creat_child_bonus.c \
		./bonus/src/components/error_handling_bonus.c \
		./bonus/src/components/find_command_path_bonus.c \
		./bonus/src/components/her_doc_bonus.c \
		./bonus/src/components/pipex_utils_bonus.c \
		./bonus/src/lib/ft_split_bonus.c \
		./bonus/src/lib/ft_strdup_bonus.c \
		./bonus/src/lib/ft_strjoin_bonus.c \
		./bonus/src/lib/ft_strlen_bonus.c \
		./bonus/src/lib/ft_strncmp_bonus.c \
		./bonus/src/lib/ft_strtok_bonus.c \
		./bonus/get_next_line/get_next_line_bonus.c \
		./bonus/get_next_line/get_next_line_utils_bonus.c \

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

all: ${NAME}

bonus: ${NAMEB}

clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@$(RM) $(OBJS) $(OBJSB)

fclean: clean
	@printf "$(RED)Removing executable...$(RESET)\n"
	@$(RM) ${NAME} ${NAMEB}

re: fclean all

.PHONY: all bonus clean fclean re
