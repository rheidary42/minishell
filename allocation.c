/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:57:48 by rheidary          #+#    #+#             */
/*   Updated: 2026/01/06 18:02:09 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TO-DO pre-set all values to NULL so if conditions work properly
void	free_env(t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	if (!env)
		return ;
	curr = *env;
	while (curr != NULL)
	{
		tmp = curr->next;
		if (curr->name)
			free(curr->name);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = tmp;
	}
//	free(env);
	*env = NULL;
}

// TO-DO pre-set all values to NULL so if conditions work properly
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
		if (curr->expanded)
			free(curr->expanded);
		if (curr->value)
			free(curr->value);
		free(curr);
		curr = tmp;
	}
	*tokens = NULL;
}

// TO-DO pre-set all values to NULL so if conditions work properly
void	free_redir(t_redir **redir)
{
	t_redir	*curr;
	t_redir	*tmp;

	if (!redir)
		return ;
	curr = *redir;
	while (curr != NULL)
	{
		tmp = curr -> next;
		if (curr->file != NULL)
			free(curr->file);
		free(curr);
		curr = tmp;
	}
	*redir = NULL;
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
			free_redir(&curr->redir);
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