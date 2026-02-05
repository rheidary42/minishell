/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:23:09 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/05 14:25:21 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(t_shell *shell)
{
	char	**arr;

	if (shell->line[0] == '\0')
		return (NULL);
	arr = split(shell);
	if (arr[0] == NULL)
		return (NULL);
	build_token_list(shell, arr);
	if (!validate_tokens(shell->tokens))
	{
<<<<<<< HEAD:src/parsing/parse.c
		write(STDERR_FILENO, "minishell: syntax error\n", 25);
=======
		write(1,"minishell: syntax error\n", 25);
>>>>>>> 2327a4f (fix: multiple heredoc support, signals working with heredoc and normally, removed TOKEN_EOF):parse.c
		shell->last_exit_status = 2;
		return (NULL);
	}
	return (shell->tokens);
}

int	parse(t_shell *shell)
{
	if (tokenize(shell) == NULL)
		return (EXIT_FAILURE);
	parameter(shell);
	word(shell);
	quote_removal(shell);
	build_commands(shell);
	return (EXIT_SUCCESS);
}