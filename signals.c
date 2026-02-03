#include "minishell.h"

volatile sig_atomic_t g_sig = 0;

void	sigint_handler(int sig)
{
	(void)sig;
	g_sig = 1;
}

int	rl_ev_hook(void)
{
	if (g_sig)
	{
		g_sig = 0;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	return (0);
}

void	setup_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}