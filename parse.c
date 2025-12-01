/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:23:09 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/18 15:20:28 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(t_shell *shell)
{
	char	**arr;

	if (shell->line[0] == '\0')
		return (NULL);
	arr = split(shell);
	build_token_list(shell, arr);
	// clean arguments
	if (!validate_tokens(shell->tokens))
	{
		//cleanup
		exit(1);
	}
	return (NULL);
}

void	parse(t_shell *shell)
{
	tokenize(shell);
	parameter(shell);
	build_commands(shell);
	// while (state == in_quote)
	// {
	// 	readline()
	// 	append;
	// }
	// commandize();
	// expand();
}