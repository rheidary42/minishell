/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:57:48 by rheidary          #+#    #+#             */
/*   Updated: 2025/10/23 12:17:48 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*safe_malloc(size_t size, t_shell *shell)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		clean_up(shell);
		exit(0);
	}
	return (ptr);
}

void	free_tokens(t_token **tokens)
{
	t_token	*curr;
	t_token	*tmp;

	if (!tokens)
		return ;
	curr = *tokens;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->value != NULL)
			free(curr->value);
		free(curr);
		curr = tmp;
	}
	*tokens = NULL;
}

void	free_cmds(t_cmd **cmds)
{
	t_cmd	*curr;
	t_cmd	*tmp;

	if (!cmds)
		return ;
	curr = *cmds;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->argv != NULL)
			free(curr->argv);
		if (curr->redir != NULL)
			free(curr->redir);
		free(curr);
		curr = tmp;
	}
	*cmds = NULL;
}

void	clean_up(t_shell *shell)
{
	if (!shell)
		return ;
	free_tokens(&shell->tokens);
	free_cmds(&shell->cmds);
}