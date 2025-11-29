#ifndef MINISHELL_H
# define MINISHELL_H

/* External libraries*/
# include "libs/libft/libft.h"

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

extern volatile sig_atomic_t	g_sig;

typedef enum e_toktype
{
    TOKEN_WORD,        // command or argument
    TOKEN_PIPE,        // |
    TOKEN_REDIR_IN,    // <
    TOKEN_REDIR_OUT,   // >
    TOKEN_APPEND,      // >>
    TOKEN_HEREDOC,     // <<
    TOKEN_EOF          // end of input
}   t_toktype;

typedef struct s_token
{
    t_toktype       type;
    char            *value;
	char			*expanded;
	bool			*dq_mask;
	bool			is_expanded;
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

typedef struct s_redir
{
	t_toktype       type;
	char            *file;
    int             heredoc_fd;
    struct s_redir  *next;
    struct s_redir  *prev;
}	t_redir;

typedef struct  s_env
{
    char    		*name;
    char    		*value;
    struct s_env	*next;
}   t_env;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redir;
    char    *redir_output; // for execution later
	int		redir_count;
    struct  s_cmd   *next;
}	t_cmd;

typedef struct s_shell
{
    t_cmd   *cmds;
    t_token *tokens;
    t_env   *env;
    char    *line;
    int     last_exit_status;
}   t_shell;

typedef struct  s_exec
{
    char    **all_paths;
    char    *paths_from_env;
    char    *final_path;
    int     pipe_fds[2];
    int     prev_fd;
    int     file_fd;
    pid_t   child;
    pid_t   last_child;
}   t_exec;


void	print_list(t_shell *shell);
void	build_token_list(t_shell *shell, char **arr);
int	validate_tokens(t_token *tokens);
char	**split(t_shell *shell);

void	parse(t_shell *shell);
t_token	*tokenize(t_shell *shell);
int	    token_len(char *str);
void	build_commands(t_shell *shell);

        //ALLOCATION
void	*safe_calloc(size_t size, t_shell *shell);
void	clean_up(t_shell *shell);

        //HELPERS
char	*ft_safe_strdup(const char *s, t_shell *shell);
char	*ft_strcpy(char *dest, char *src);

        //EXECUTION HELPERS
char	*str_join3(char *s1, char *s2, char *s3, t_shell *shell);
bool	is_direct_path(char *executable);
void	initialise_exec(t_exec *exec);
int     count_path(char *paths_from_env);
char	*get_paths_from_env(t_env *env);
char	**split_paths(char *paths_from_env, t_shell *shell);
void	apply_redir(t_shell *shell, t_cmd *cmd, t_redir *redirection, t_exec *exec);
char	*check_executable(char **all_paths, char *cmd_name, t_shell *shell);
void	path_lookup(char *cmd_name, t_shell *shell, t_exec *exec);
void	free_and_close(t_shell *shell, t_cmd *cmd, t_exec *exec);
void	free_func(char **to_free);
        //EXECUTION

int	execution(t_shell *shell);
int	exec_ext_cmd(t_shell *shell, t_cmd *cmd, t_exec *exec);
int	exec_single_cmd(t_shell *shell, t_exec *exec);
void	exec_in_child(t_shell *shell, t_cmd *cmd, t_exec *exec);
int	build_pipeline(t_shell *shell, t_exec *exec);
int	make_envp(t_env *copy_env, char **curr_env);
char	**convert_envp(t_shell *shell);
int	free_env_list(t_env *head);
int	handle_heredoc(t_shell *shell, char *delim);


// EXPANSIONS // WILL FORMAT EVENTUALLY
void	parameter(t_shell *shell);
size_t	exit_status_len(int i);
int		ifs(char c);
void	copy_char_expansion(size_t *i, char *dest, char c);

#endif