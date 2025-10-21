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

#endif