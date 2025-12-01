/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 16:53:58 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/12 16:13:40 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	full_exit(t_shell *shell)
{
	rl_clear_history();
	free_env(&shell->env);
	free(shell->line);
	free(shell);
}

int main(int ac, char **av, char **envp)
{
	t_shell	*shell;
	char	*tmp_line;

	(void)ac; (void)av;
	shell = ft_calloc(1, sizeof(t_shell));
	if (shell == NULL)
		return (EXIT_FAILURE);
	shell->env = ft_calloc(1, sizeof(t_env));
	if (make_envp(shell->env, envp) == 0)
		return (EXIT_FAILURE);
	while (true)
	{
		if (isatty(fileno(stdin)))
			shell->line = readline("minishell>");
		else
		{
			tmp_line = get_next_line(fileno(stdin));
			// if (tmp_line == NULL)
			// 	exit(32);
			shell->line = ft_strtrim(tmp_line, "\n");
			free(tmp_line);
		}
		if (shell->line == NULL)	// If EOF (CTRL-D) detected exit
		{
			full_exit(shell);
			exit(0);
		}
		parse(shell);
		// if (shell->line[0] != '\0')	// Check for empty input to not clog history with empty lines
		// 	add_history(shell->line);
		execution(shell);
		clean_up(shell);
		// free
	}
	full_exit(shell);
	return (0);
}
