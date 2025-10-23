/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:23:09 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/23 12:39:40 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(t_shell **shell)
{
	char **arr;

	arr = split(*shell);
	build_token_list(&((*shell)->tokens), arr);
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

void	parse(t_shell **shell)
{
	tokenize(shell);
	// commandize();
	// expand();
}