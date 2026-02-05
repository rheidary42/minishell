#include "minishell.h"

void	print_list(t_shell *shell)
{
	// t_token *curr = shell->tokens;

	// while (curr != NULL)
	// {
	// 	printf("%s ; ", curr -> value);
	// 	printf("%i ; ", curr -> type);
	// 	printf("%p\n", curr -> prev);
	// 	curr = curr->next;
	// }
	t_cmd	*curr = shell->cmds;
	while (curr != NULL)
	{
		for (int i = 0; curr->argv[i] != NULL; i++)
			printf("%s\n", curr->argv[i]);
		free(curr->argv);
		curr = curr->next;
	}
}

void	free_split_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_list(t_shell *shell)
{
	t_token	*curr;
	t_token	*onebehind;

	// if (head == NULL)
	// 	return ;
	curr = shell->tokens;
	while (curr != NULL)
	{
		onebehind = curr;
		curr = curr->next;
		free(onebehind->value);
		free(onebehind);
	}
	shell->tokens = NULL;
}

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
	if (new == NULL)
		return (NULL);
	new->type = token_type(str);
	new->value = (char *)arena_push(shell->arena, ft_strlen(str) + 1, 0, shell);
	ft_strlcpy(new->value, str, ft_strlen(str) + 1);
	new->expanded = NULL;
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
		if (new == NULL)
			return (free_list(shell));
		append_node(shell, new);
		i++;
	}
}
//TEST TOKENIZER
void	print_cmds(t_token **tokens, t_cmd **cmds)
{
	t_cmd *curr;
	curr = *cmds;
	for (int i = 0; curr->next != NULL; i++)
	{
		for (int j = 0; curr->argv[j] != NULL; j++)
		{
			printf("%s ; ", curr->argv[j]);
		}
		printf("%i; %s", curr->redir->type, curr->redir->file);
	}
}

// int	main(void)
// {
// 	t_shell	*shell;
// 	t_cmd	*curr;
// 	t_token	*curr_token;

// 	shell = ft_calloc(1, sizeof(t_shell));

// 	shell->line = ft_safe_strdup("< Makefile cat \"This is not a test\"| wc -l > output.txt", shell);
// 	parse(shell);
// 	curr = shell->cmds;

// 	curr_token = shell->tokens;
// 	while (curr_token != NULL)
// 	{
// 		printf("%s\n", curr_token->value);
// 		curr_token = curr_token->next;
// 	}

// 	printf("\n--- Commands ---\n");

// 	while (curr != NULL)
// 	{
// 		for (int j = 0; curr->argv[j] != NULL; j++)
// 			printf("ARGV=%s ; ", curr->argv[j]);
		
// 		t_redir	*r = curr->redir;
// 		while (r != NULL)
// 		{
// 			r = r->next;
// 		}
// 		curr = curr->next;
// 		printf("\nnext command\n");
// 	}
// 	free_list(shell);
// 	free(shell->line);
// 	free(shell);
// }