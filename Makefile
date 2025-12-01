# --- colors ---

RED		:= \033[0;31m
GREEN	:= \033[0;32m
YELLOW	:= \033[0;33m
CYAN	:= \033[0;36m
ORANGE	:= \033[38;5;214m
RESET	:= \033[0m
BOLD	:= \033[1m

# --- config ---

NAME := minishell
HEADER := minishell.h
CFLAGS := -g -I. -lreadline -g3
# -Wall -Wextra -Werror

LIBFT := libs/libft/libft.a
GNL_PATH := libs/get_next_line
GNL_SRCS := $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c
SRCS =	main.c\
		parse.c\
		split.c\
		token_list.c\
		allocation.c\
		build_commands.c\
		convert_envp.c\
		envp.c\
		exec_helper.c\
		exec_paths.c\
		exec_pipeline.c\
		exec_single_command.c\
		execution.c\
		helper1.c\
		heredoc.c\
		param_helper.c\
		signals.c\
		validate_tokens.c\
		expansion.c\
		$(GNL_SRCS)\

OBJS := $(SRCS:.c=.o)

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
	@rm -f $(NAME)
	@make clean -sC libs/libft
	@make fclean -sC libs/libft

re: fclean all

.PHONY: all clean fclean re