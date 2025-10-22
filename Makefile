# --- colors ---

RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
CYAN	:= \033[0;36m
ORANGE	:= \033[38;5;214m
RESET	:= \033[0m
BOLD	:= \033[1m

# --- config ---

NAME := Minishell
HEADER := minishell.h
CFLAGS := -g -I.
# -Wall -Wextra -Werror

LIBFT := libs/libft/libft.a

SRC =	main.c\
		parse.c\
		split.c\
		token_list.c\

OBJS := $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

# --- libraries ---

$(LIBFT):
	@make -sC libs/libft

# --- cleaning ---

clean:
	@rm -f $(OBJS)
	@make clean -sC libs/libft

fclean:
	@rm -f $(OBJS)
	@make clean -sC libs/libft
	@make fclean -sC libs/libft

re: f all

.PHONY: all clean fclean re