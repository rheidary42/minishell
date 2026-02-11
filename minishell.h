/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 06:10:15 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 16:18:34 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* External libraries*/
# include "libs/libft/libft.h"
# include "libs/get_next_line/get_next_line.h"

/* Standard library + memory + strings */
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdbool.h>

/* File descriptors, open(), access(), stat(), etc */
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

/* Directory handling (opendir, readdir, closedir) */
# include <dirent.h>

/* Errors (perror, strerror) */
# include <errno.h>

/* Signals (signal, sigaction, sigemptyset, sigaddset, kill) */
# include <signal.h>

# include <bits/sigaction.h>
/* Waiting (wait, waitpid, wait3, wait4) */
# include <sys/wait.h>

/* TTY / Terminal control (isatty, ttyname, ttyslot, ioctl) */
# include <sys/ioctl.h>

/* Termcap / Termios (tgetent, tputs, etc) */
# include <termios.h>
# include <termcap.h>

/* Readline */
# include <readline/readline.h>
# include <readline/history.h>

/* Arena headers */
# include <stdint.h>

extern volatile sig_atomic_t	g_sig;

typedef int8_t					t_i8;
typedef int16_t					t_i16;
typedef int32_t					t_i32;
typedef int64_t					t_i64;
typedef uint8_t					t_u8;
typedef uint16_t				t_u16;
typedef uint32_t				t_u32;
typedef uint64_t				t_u64;

typedef t_i8					t_b8;
typedef t_i32					t_b32;

# define KIB 1024 

typedef struct s_struct
{
	t_u64	capacity;
	t_u64	pos;
}	t_mem_arena;

typedef struct s_pos
{
	size_t	org;
	size_t	exp;
}	t_pos;

typedef enum e_quote
{
	NO_QUOTE = 0,
	DOUBLE_QUOTE = 1,
	SINGLE_QUOTE = 2
}	t_quote;

typedef enum e_toktype
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}	t_toktype;

typedef enum e_builtins
{
	EECHO,//EECHO because ECHO already exists
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
}	t_builtins;

typedef struct s_token
{
	t_toktype		type;
	char			*value;
	char			*expanded;
	bool			*ws_mask;
	bool			is_expanded;
	bool			was_quoted;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_redir
{
	struct s_redir	*next;
	struct s_redir	*prev;
	t_toktype		type;
	char			*file;
	int				heredoc_fd;
	bool			was_quoted;
}	t_redir;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			exported;
	int				has_equal_sign;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redir;
	char			*redir_output; // for execution later
	int				redir_count;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_exec
{
	char	**all_paths;
	char	*paths_from_env;
	char	*final_path;
	int		pipe_fds[2];
	int		prev_fd;
	int		file_fd;
	int		sig_flag;
	int		errno_save;
	pid_t	child;
	pid_t	last_child;
}	t_exec;

typedef struct s_shell
{
	t_cmd		*cmds;
	t_token		*tokens;
	t_env		*env;
	t_exec		*exec;
	char		*line;
	bool		is_interactive;
	int			last_exit_status;
	int			save_stdin;
	int			save_stdout;
	int			shlvl;
	t_mem_arena	*arena;
}	t_shell;

/*      		EXECUTION           */
//  execution.c
int					execution(t_shell *shell);
void				path_lookup(char *cmd_name, t_shell *shell, t_exec *exec);

//  exec_single_command.c
int					exec_single_cmd(t_shell *shell, t_exec *exec);
int					exec_in_child(t_shell *shell, t_cmd *cmd, t_exec *exec);
void				exec_in_child_helper(t_shell *shell,
						t_cmd *cmd, t_exec *exec);
int					apply_redir(t_shell *shell,
						t_redir *redirection, t_exec *exec);
int					consume_redirs_only(t_redir *redir);

// exec_single_command_helper.c
int					set_exit_status(t_shell *shell);
char				**set_envp(t_shell *shell,
						t_cmd *cmd, t_exec *exec, int *builtin_id);
void				no_final_path(t_shell *shell, t_cmd *cmd,
						t_exec *exec, char **envp);
void				read_errno(t_shell *shell, t_cmd *cmd, t_exec *exec);
void				detect_signals(t_shell *shell, int status);

//  exec_pipeline.c
int					build_pipeline(t_shell *shell, t_exec *exec);
void				exec_cmd(t_shell *shell, t_cmd *cmd, t_exec *exec);
void				wait_for_children(t_shell *shell, t_exec *exec);
void				redirection(t_exec *exec);
void				fork_failure(t_shell *shell, t_cmd *cmd, t_exec *exec);

// exec_paths.c
char				*check_executable(char **all_paths,
						char *cmd_name, t_shell *shell);
char				**split_paths(char *paths_from_env, t_shell *shell);
char				*split_paths_helper(t_shell *shell,
						char *paths, int *e, int *s);
int					count_path(char *paths_from_env);
char				*get_paths_from_env(t_env *env);

//  exec_helper.c
char				*str_join3(char *s1, char *s2, char *s3, t_shell *shell);
void				str_join3_helper(char *s1, char *s2);
bool				is_direct_path(char *executable);
void				initialise_exec(t_exec *exec);

/*      			    BUILTINS           */
//  builtins.c
int					is_builtin(char *cmd);
int					exec_builtin(t_shell *shell, t_cmd *cmd,
						t_env *env, int builtin_id);

//  cd.c			
int					ft_cd(t_env *env, t_cmd *cmd);
int					solo_cd(t_env *env);
int					update_pwd(t_env *env, char *oldpwd, char *pwd);

//  echo.c
int					ft_echo(t_cmd *cmd);
bool				is_flag(char *str);

//  env.c
int					ft_env(t_env *env);

//  exit.c
int					ft_exit(t_shell *shell, t_cmd *cmd);
void				handle_single_arg(t_shell *shell, t_cmd *cmd, char *s);

//  exit_helper.c
void				handle_exit_error(t_shell *shell, char *arg, char *s);
void				cleanup_and_exit(t_shell *shell, int exit_code);
long				ft_atol(char *s);
int					is_num(char *s);

//  export.c
int					ft_export(t_shell *shell, t_env *env, t_cmd *cmd);
int					process_var(t_env *env, char *var);
int					new_var(t_env *env, char *var);
void				just_export(t_env *env);
int					validate_id(char *s);

//  pwd.c
int					change_var(t_env *curr, char *var, int id_len);
int					ft_pwd(void);

//  unset.c
int					ft_unset(t_env *env, t_cmd *cmd);
void				del_node(t_env *env, char *str);
int					is_valid_id(char *str);

/*      			    ENVIRONMENT         */
//  convert_envp.c
char				**convert_envp(t_shell *shell);
int					env_list_size(t_env *env);

//  envp.c
int					copy_envp(t_shell *shell, t_env *copy_env, char **curr_env);
int					make_envp(t_shell *shell, t_env *copy_env);
int					add_env_var(t_shell *shell, t_env *node,
						char *name, char *value);
int					copy_var(t_env *env, char *str);
size_t				strlen_delim(char *str, char delim);

//  shlvl.c
void				signal_and_shlvl(t_shell *shell);
int					set_shlvl(t_shell *shell);
t_env				*find_node(t_env *env);
void				set_interactive_mode(t_shell *shell);

/*      			    MEMORY          */
//  arena.c
void				arena_clear(t_mem_arena *arena);
void				arena_pop_to(t_mem_arena *arena, t_u64 pos);
void				arena_pop(t_mem_arena *arena, t_u64 size);
void				*arena_push(t_mem_arena *arena, t_u64 size, t_b32 non_zero,
						t_shell *shell);
t_mem_arena			*arena_create(t_u64 capacity);

//  cleanup.c
void				close_shell_fds(t_shell *shell);
void				close_exec_fds(t_exec *exec);
void				full_exit(t_shell *shell, int exit_code);
void				free_and_close(t_shell *shell, t_cmd *cmd, t_exec *exec);
void				free_env(t_env **env);

/*      			    MISC            */
//  heredoc.c
int					heredoc_collector(t_shell *shell);
int					init_heredoc(t_shell *shell, t_redir *r);
int					run_heredoc(t_shell *shell, char *tmp_file,
						char *delim, bool was_q);
char				*heredoc_expander(t_shell *shell, char *line);

//  heredoc_expander.c
int					expand_var(t_shell *shell, char *exp_line,
						char *line, int *exp_i);
void				copy_exit_code(t_shell *shell, char *exp_line, int *exp_i);
int					full_line_len(t_shell *shell, char *line);
char				*var_name(t_shell *shell, char *s);
int					var_len(char *s);

//  heredoc_helper.c
char				*get_here_doc_name(t_shell *shell);
void				handle_exp(t_shell *shell, char *line, int fd);
char				*gnl_mode(void);
int					handle_sigint(char *line, int fd);
int					handle_eof(char *line, char *delim);

//  signals.c
void				setup_signals(t_shell *shell);
void				setup_prompt_signals(void);
void				setup_noninteractive_signals(void);
int					rl_ev_hook(void);
void				sig_err_msg(t_shell *shell, int sig_num);

//  signal_handler.c
void				sigint_handler(int sig);

/*      			    PARSING         */
//  build_commands.c
t_cmd				*create_append(t_shell *shell, t_token *curr_token, int *i);
void				append_redir(t_cmd *cmd, t_token *token, t_shell *shell);
void				handle_redir(t_cmd *curr_cmd,
						t_token **curr_token_ptr, t_shell *shell);
void				build_commands(t_shell *shell);

//  build_commands_helper.c
int					count_argc(t_token *tokens);
void				finish_argv(t_cmd **cmd, int *i);
bool				is_redir(t_token *token);
bool				is_argv(t_token *token);

//  parse.c
int					parse(t_shell *shell);
t_token				*tokenize(t_shell *shell);

//  split.c
char				**split(t_shell *shell);
int					count_tokens(char *str);
int					token_len(char *str);
int					is_delim(char *str);
void				handle_quote(char *str, int *len);

//  token_list.c
void				build_token_list(t_shell *shell, char **arr);
t_token				*new_node(char *str, t_shell *shell);
t_toktype			token_type(char *str);
void				append_node(t_shell *shell, t_token *new);

//  validate_tokens.c
int					validate_tokens(t_token *tokens);
int					is_unclosed_quote(char *str);
int					is_pipe(t_token *token);
int					is_redir2(t_token *tok);

/*      			    EXPANSION           */
//  quote.c
bool				needs_removal(t_token *token);
char				*remove_quotes(char *value, t_shell *shell);
void				quote_removal(t_shell *shell);

// word.c
t_token				*split_token_segments(t_token *token, t_shell *shell,
						t_token *first, t_token *prev);
void				split_value(t_token *token, t_shell *shell);
bool				is_whitespace_token(t_token *curr);
void				word(t_shell *shell);

// word2.c
bool				is_ifs(char c);
bool				needs_splitting(t_token *curr);
int					calc_token_size(t_token *token, int *index);
t_token				*make_base_token(t_token *src,
						int start, int len, t_shell *shell);
void				splice_token(t_token *old, t_token *first, t_token *last,
						t_shell *shell);

// word3.c
void				generate_base_tokens(t_token *curr, t_shell *shell);
t_token				*make_split_token(t_token *src,
						int start, int len, t_shell *shell);
int					next_split_length(char *str);

/*      			    PARAMETER           */
//  expansion_core.c
void				parameter(t_shell *shell);
void				expand_value(t_token *token, t_shell *shell, size_t len);

//  expansion_insert.c
void				handle_var(t_pos *pos, t_quote *quote_state,
						t_token *token, t_shell *shell);
void				insert_exit_status(t_pos *pos,
						t_token *token, t_shell *shell);

//  expa			nsion_size.c
size_t				calc_expanded_size(char *value, t_shell *shell);
int					needs_expansions(t_token *token);

//  expa			nsion_var.c
char				*get_var_value(char *var_name, t_shell *shell);
char				*get_var_name(t_shell *shell,
						char *value, size_t *var_start);
size_t				get_var_len(char *value, int *var_start, t_shell *shell);

//  para			m_helper.c
char				*ft_strcpy(char *dest, char *src);
void				update_quote_state(char c, t_quote *quote_state);
int					is_expandable_var(char *value,
						size_t index, t_quote in_quote);
int					ifs(char c);
size_t				exit_status_len(int i);

// FIX L			ATER
bool				is_ifs(char c);

#endif			
