/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:23:09 by rheidary          #+#    #+#             */
/*   Updated: 2026/01/09 16:08:20 by rheidary         ###   ########.fr       */
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
	// clean arguments
	if (!validate_tokens(shell->tokens))
	{
		write(STDERR_FILENO, "minishell: syntax error\n", 25);
		shell->last_exit_status = 2;
		return (NULL);
	}
	return (NULL);
}

void	parse(t_shell *shell)
{
	tokenize(shell);
	parameter(shell);
	word(shell);
	quote_removal(shell);
	build_commands(shell);
	// while (state == in_quote)
	// {
	// 	readline()
	// 	append;
	// }
	// commandize();
	// expand();
}