/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:53:58 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/03 17:03:40 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void)ac; (void)av; (void)envp;
	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	shell->env = ft_calloc(1, sizeof(t_env));
	if (make_envp(shell->env, envp) == 0)
		return (EXIT_FAILURE);
	while (true)
	{
		shell->line = readline("minishell>");
		if (shell->line == NULL)	// If EOF (CTRL-D) detected exit
			exit (0);
		parse(shell);
		if (shell->line[0] != '\0')	// Check for empty input to not clog history with empty lines
			add_history(shell->line);
		// execute
		// free
	}
	return (0);
}
