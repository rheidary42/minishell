/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 03:43:59 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/18 02:03:28 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_sig = 0;

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

int	rl_ev_hook(void)
{
	if (g_sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		rl_done = 1;
	}
	return (0);
}

void	setup_noninteractive_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_prompt_signals(void)
{
	struct sigaction	sa;
	struct sigaction	sa_quit;

	rl_event_hook = rl_ev_hook;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa_quit.sa_handler = SIG_IGN;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	setup_signals(t_shell *shell)
{
	if (shell->is_interactive == true)
		setup_prompt_signals();
	else
		setup_noninteractive_signals();
}
