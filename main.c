/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:53:58 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/23 12:30:41 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*line;
	t_shell	*shell;

	(void)ac; (void)av; (void)envp;
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell == NULL)
		return (1);
	while (true)
	{
		shell->line = readline("minishell>");
		if (shell->line == NULL)	// If EOF (CTRL-D) detected exit
			exit (0);
		if (line[0] != '\0')	// Check for empty input to not clog history with empty lines
			add_history(line);
		parse(shell);
		// execute
		// free
	}
	return (0);
}