/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:53:58 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/20 16:14:25 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **envp)
{
	char	*line;

	(void)ac; (void)av; (void)envp;
	while (true)
	{
		line = readline("minishell>");
		if (!line)	// If EOF (CTRL-D) detected exit
			exit (0);
		if (line[0] != '\0')	// Check for empty input to not clog history with empty lines
			add_history(line);
		parse(line);
		// execute
		// free
	}
	return 0;
}