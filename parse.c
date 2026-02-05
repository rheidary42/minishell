/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:23:09 by rheidary          #+#    #+#             */
/*   Updated: 2026/02/05 14:06:40 by rheidary         ###   ########.fr       */
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
		perror("minishell: syntax error\n");
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