/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 12:23:09 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/22 14:11:36 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*tokenize(char *line)
{
	t_token	*tokens;
	t_cmd	*cmd;
	char **arr;

	arr = split(line);
	build_token_list(&tokens, arr);
	// clean arguments
	if (!validate_tokens(tokens))
	{
		//cleanup
		exit(1);
	}
	build_cmds(&cmd, &tokens);
	print_list(tokens);
	assign_values();
}

void	parse(char *line)
{
	tokenize(line);
	commandize();
	expand();
}