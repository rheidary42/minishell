#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

void	sig_err_msg(t_shell *shell, int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "\n", 1);
	}
	if (sig_num == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
	}
	shell->last_exit_status = 128 + sig_num;
}

void	heredoc_sig_handler(int sig)
{
	(void)sig;
	g_sig = SIGINT;
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_sig = SIGINT;
}

int	rl_ev_hook(void)
{
	if (g_sig == SIGINT)
	{
		// g_sig = 0;
		// write(1, "\n", 1);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

void	setup_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sa_quit;
	rl_event_hook = rl_ev_hook;
	sa.sa_handler = heredoc_sig_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
	// signal(SIGINT, sigint_handler);
	// signal(SIGQUIT, SIG_IGN);
}