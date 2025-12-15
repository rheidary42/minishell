/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rheidary <rheidary@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 20:23:59 by rheidary          #+#    #+#             */
/*   Updated: 2025/12/15 17:56:26 by rheidary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	Calculate the length of the variable's value for expansion
size_t	get_var_len(char *value, int *var_start, t_shell *shell)
{
	char	*var_name;
	int		var_end;
	t_env	*head;
	size_t	len;

	len = 0;
	if (value[*var_start] == '?')
		return (*var_start += 1, exit_status_len(shell->last_exit_status));
	var_end = *var_start;
	while (value[var_end] && (ft_isalnum(value[var_end])) != 0)
		var_end++;
	var_name = ft_substr(value, *var_start, var_end - *var_start);
	head = shell->env;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, var_name) == 0)
		{
			len = ft_strlen(head->value);
			break ;
		}
		head = head->next;
	}
	*var_start = var_end;
	return (free(var_name), len);
}

size_t	calc_expanded_size(char *value, t_shell *shell)
{
	size_t	len;
	int		i;

	len = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'' && ++i && ++len)
		{
			while (value[i] != '\0' && value[i] != '\'' && i++)
				len++;
			i++;
			len++;
		}
		else if (is_expandable_var(value, i, NO_QUOTE) && ++i)
			len += get_var_len(value, &i, shell);
		else if (++i)
			len++;
	}
	return (len);
}

// Add '_' potentially, ask around and look in manual
// INFO: '_' only in POSIX implementations -> Fuck it (?)
int	needs_expansions(t_token *token)
{
	int	i;

	if (token->type != TOKEN_WORD || token->value == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '\'')
		{
			i++;
			while (token->value[i] != '\'')
				i++;
			i++;
			if (token->value[i] == '\0')
				return (EXIT_FAILURE);
		}
		if (is_expandable_var(token->value, i, NO_QUOTE))
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}

char	*get_var_value(char *var_name, t_shell *shell)
{
	t_env	*head;

	head = shell->env;
	while (head != NULL)
	{
		if (ft_strcmp(head->name, var_name) == 0)
		{
			free(var_name);
			return (ft_strdup(head->value));
		}
		head = head->next;
	}
	free(var_name);
	return (NULL);
}

char	*get_var_name(char *value, size_t *var_start)
{
	size_t	var_end;
	char	*var_name;

	var_end = *var_start;
	while (value[var_end] && (ft_isalnum(value[var_end])) != 0)
		var_end++;
	var_name = ft_substr(value, *var_start, var_end - *var_start);
	*var_start = var_end;
	return (var_name);
}

void	insert_exit_status(t_pos *pos, t_token *token, t_shell *shell,
			t_quote *quote_state)
{
	char	*exit_status;
	char	*dest;
	int		exit_len;
	int		i;

	exit_status = ft_itoa(shell->last_exit_status);
	if (exit_status == NULL)
		clean_up(shell);
	dest = shell->tokens->expanded + pos->exp;
	exit_len = exit_status_len(shell->last_exit_status);
	i = -1;
	while (++i < exit_len)
	{
		if (*quote_state == DOUBLE_QUOTE)
			token->ws_mask[pos->exp + i] = true;
		token->expanded[pos->exp + i] = exit_status[i];
	}
	pos->exp += exit_len;
	free(exit_status);
}

void	handle_var(t_pos *pos, t_quote *quote_state,
			t_token *token, t_shell *shell)
{
	char	*var_value;
	size_t	var_len;
	size_t	j;

	if (*quote_state != SINGLE_QUOTE)
		pos->val++;
	if (token->value[pos->val] == '?')
	{
		insert_exit_status(pos, token, shell, quote_state);
		pos->val++;
		return ;
	}
	var_value = get_var_value(get_var_name(token->value, &pos->val), shell);
	if (!var_value)
		return ;
	j = 0;
	var_len = ft_strlen(var_value);
	while (j < var_len)
	{
		token->expanded[pos->exp] = var_value[j];
		token->ws_mask[pos->exp] = (*quote_state == NO_QUOTE);
		pos->exp++;
		j++;
	}
	free(var_value);
}

//	Copy characters from token->value to token->expanded, expanding $vars
//	pos.val = index in token->value
//	pos.exp = index in token->expanded
void	expand_value(t_token *token, t_shell *shell, size_t len)
{
	t_quote			quote_state;
	t_pos			pos;

	token->expanded = safe_calloc(len + 1, shell);
	token->ws_mask = safe_calloc(len, shell);
	quote_state = NO_QUOTE;
	pos.val = 0;
	pos.exp = 0;
	while (pos.exp < len)
	{
		if (is_expandable_var(token->value, pos.val, quote_state))
			handle_var(&pos, &quote_state, token, shell);
		else
		{
			update_quote_state(token->value[pos.val], &quote_state);
			token->expanded[pos.exp++] = token->value[pos.val++];
		}
	}
}

void	parameter(t_shell *shell)
{
	t_token	*curr;

	curr = shell->tokens;
	while (curr != NULL)
	{
		if (needs_expansions(curr) == EXIT_SUCCESS)
		{
			curr->is_expanded = true;
			expand_value(curr, shell, calc_expanded_size(curr->value, shell));
		}
		else
		{
			curr->is_expanded = false;
			curr->expanded = NULL;
			curr->ws_mask = NULL;
		}
		curr = curr->next;
	}
}

// ////////////////////////////////////

// // Check if anything has been expanded in DQ
// bool	needs_splitting(t_token *curr)
// {
// 	int		i;
// 	char	*value;

// 	i = 0;
// 	value = curr->expanded;
// 	while (value[i] != '\0')
// 	{
// 		if (curr->ws_mask[i] == true)
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

// // Create multiple tokens out of one
// /*NOTES:
// 	Preserve leading IFS */
// void	split_value(t_token *token)
// {
	
// }

// /* TO-DO*/
// void	word(t_shell *shell)
// {
// 	t_token	*curr;

// 	// CASE 1.2: EOB
// 	if (shell->tokens->expanded == 0)
// 		return ;
// 	// CASE 1.1
// 	curr = shell->tokens;
// 	while (curr != NULL)
// 	{
// 		if (curr->is_expanded == true && needs_splitting(curr) == true)
// 		{
// 			split_value(curr);
// 		}
// 		curr = curr->next;
// 	}
// }

// ////////////////////////////////////

/* TO-DO*/
// void	quote(t_shell *shell)
// {
	
// }

///////////////////////////////////////

// void	expand(t_shell *shell)
// {
// 	parameter(shell);
// 	word(shell);
// 	quote(shell);
// }

/////////////////////////////////////
/////////////////////////////////////
/////////////////////////////////////

// // === TESTER ===

// // /* Helper to create a new environment variable */
// t_env *new_env(const char *name, const char *value)
// {
//     t_env *env = malloc(sizeof(t_env));
//     if (!env)
//         return NULL;
//     env->name = strdup(name);
//     env->value = strdup(value);
//     env->next = NULL;
//     return env;
// }

// /* Helper to add env to shell */
// void add_env(t_shell *shell, t_env *env)
// {
//     if (!shell->env)
//         shell->env = env;
//     else
//     {
//         t_env *tmp = shell->env;
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = env;
//     }
// }

// /* Helper to create a new token */
// t_token *new_token(const char *value)
// {
//     t_token *token = malloc(sizeof(t_token));
//     if (!token)
//         return NULL;
//     token->value = strdup(value);
//     token->expanded = NULL;
//     token->ws_mask = NULL;
//     token->is_expanded = false;
//     token->type = TOKEN_WORD;
//     token->next = NULL;
//     token->prev = NULL;
//     return token;
// }

// /* Print expanded token values */
// void print_tokens(t_shell *shell)
// {
//     t_token *curr = shell->tokens;
//     while (curr)
//     {
//         printf("Original: [%s]\n", curr->value);
//         printf("Expanded: [%s]\n", curr->expanded ? curr->expanded : "(null)");
//         printf("Double-quote mask: ");
//         if (curr->ws_mask)
//         {
//             for (size_t i = 0; i < strlen(curr->expanded); i++)
//                 printf("%d", curr->ws_mask[i]);
//         }
//         printf("\n\n");
//         curr = curr->next;
//     }
// }

// int main(void)
// {
//     t_shell shell;
//     memset(&shell, 0, sizeof(shell));

//     /* Setup environment */
//     add_env(&shell, new_env("USER", "alice"));
//     add_env(&shell, new_env("HOME", "/home/alice"));
//     add_env(&shell, new_env("SHELL", "/bin/bash"));

//     shell.last_exit_status = 42;

//     /* Setup tokens */
// 		shell.tokens = new_token("Hello $USER!");
// 		shell.tokens->next = new_token("Your home is $HOME.");
// 		shell.tokens->next->next = new_token("\"User: $USER\"");
// 		shell.tokens->next->next->next = new_token("\"$USER\"$USER'$USER'");
// 		shell.tokens->next->next->next->next = new_token("$?'$?'\"$?\"");
// 		shell.tokens->next->next->next->next->next = new_token("$$'$'\"$$\"");

//     /* Run expansion */
//     parameter(&shell);

//     /* Print results */
//     print_tokens(&shell);

//     return 0;
// }
