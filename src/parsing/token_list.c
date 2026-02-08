/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: boenkhja <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 04:06:37 by boenkhja          #+#    #+#             */
/*   Updated: 2026/02/08 04:06:38 by boenkhja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_node(t_shell *shell, t_token *new)
{
	t_token	*curr;

	if (new == NULL)
		return ;
	if (shell->tokens == NULL)
	{
		shell->tokens = new;
		return ;
	}
	curr = shell->tokens;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = new;
	new->prev = curr;
}

t_toktype	token_type(char *str)
{
	if (ft_strncmp((const char *)str, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp((const char *)str, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (str[0] == '>')
		return (TOKEN_REDIR_OUT);
	else if (str[0] == '<')
		return (TOKEN_REDIR_IN);
	else if (str[0] == '|')
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

t_token	*new_node(char *str, t_shell *shell)
{
	t_token	*new;

	new = (t_token *)arena_push(shell->arena, sizeof(t_token), 0, shell);
	new->type = token_type(str);
	new->value = (char *)arena_push(shell->arena, ft_strlen(str) + 1, 0, shell);
	ft_strlcpy(new->value, str, ft_strlen(str) + 1);
	new->expanded = NULL;
	new->is_expanded = false;
	new->was_quoted = false;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void	build_token_list(t_shell *shell, char **arr)
{
	t_token	*new;
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		new = new_node(arr[i], shell);
		append_node(shell, new);
		i++;
	}
}
