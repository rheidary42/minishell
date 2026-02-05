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
CFLAGS := -g3 -I.
# -Wall -Wextra -Werror

LIBFT := libs/libft/libft.a
GNL_PATH := libs/get_next_line
GNL_SRCS := $(GNL_PATH)/get_next_line.c $(GNL_PATH)/get_next_line_utils.c
SRCS =	main.c\
		src/parsing/parse.c\
		src/parsing/split.c\
		src/parsing/token_list.c\
		src/memory/allocation.c\
		src/parsing/build_commands.c\
		src/environment/convert_envp.c\
		src/environment/envp.c\
		src/execution/exec_helper.c\
		src/execution/exec_paths.c\
		src/execution/exec_pipeline.c\
		src/execution/exec_single_command.c\
		src/execution/execution.c\
		src/execution/builtins/builtins.c\
		src/misc/heredoc.c\
		src/parsing/expansion/parameter/param_helper.c\
		src/misc/signals.c\
		src/parsing/validate_tokens.c\
		src/memory/arena.c\
		src/execution/builtins/echo.c\
		src/execution/builtins/pwd.c\
		src/execution/builtins/unset.c\
		src/execution/builtins/env.c\
		src/execution/builtins/export.c\
		src/execution/builtins/exit.c\
		src/execution/builtins/cd.c\
		src/parsing/expansion/parameter/expansion_core.c\
		src/parsing/expansion/parameter/expansion_insert.c\
		src/parsing/expansion/parameter/expansion_size.c\
		src/parsing/expansion/parameter/expansion_var.c\
		src/parsing/expansion/word.c\
		src/parsing/expansion/quote.c\
 		$(GNL_SRCS)\

OBJS := $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)

runval:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=all --trace-children=yes --suppressions=readline.supp ./minishell

tidy: all clean

# --- libraries ---

$(LIBFT):
	@make -sC libs/libft

# --- test target ---

TEST_NAME := expansion_test
TEST_SRC := tests/expansion_tester.c

test: $(LIBFT)
	cc -g \
		$(filter-out main.o, $(OBJS)) \
		$(TEST_SRC) \
		$(LIBFT) \
		-I. \
		-lreadline \
		-o $(TEST_NAME)

# --- cleaning ---

clean:
	@rm -f $(OBJS)
	@make clean -sC libs/libft

fclean:
	@rm -f $(OBJS)
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)
	@make clean -sC libs/libft
	@make fclean -sC libs/libft

re: fclean all

.PHONY: all clean fclean re