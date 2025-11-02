/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:23:09 by rheidary          #+#    #+#             */
/*   Updated: 2025/11/02 20:06:48 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(t_shell *shell)
{
	char **arr;

	arr = split(shell);
	build_token_list(shell, arr);
	// clean arguments
	// if (!validate_tokens((*shell)->tokens))
	// {
	// 	//cleanup
	// 	exit(1);
	// }
	build_commands(shell);
	//assign_values();
	return (NULL);
}

void	parse(t_shell *shell)
{
	tokenize(shell);
	// while (state == in_quote)
	// {
	// 	readline()
	// 	append;
	// }
	// commandize();
	// expand();
}