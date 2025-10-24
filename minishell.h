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
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

typedef struct s_redir
{
	t_toktype       type;
	char            *file;
    struct s_redir  *next;
    struct s_redir  *prev;
}	t_redir;

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
    t_cmd   *cmds;    t_token *tokens;
    char    *line;
}   t_shell;

void	print_list(t_token *tokens);
void	build_token_list(t_token **tokens, char **arr);
char	**split(t_shell *shell);
void	build_commands(t_shell **shell);

void	parse(t_shell **shell);
t_token	*tokenize(t_shell **shell);
void	build_commands(t_shell **shell);

        //ALLOCATION
void	*safe_calloc(size_t size, t_shell *shell);

#endif