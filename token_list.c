#include "minishell.h"

void	print_list(t_shell *shell)
{
	t_token *curr = shell->tokens;

	while (curr != NULL)
	{
		printf("%s ; ", curr -> value);
		printf("%i ; ", curr -> type);
		printf("%p\n", curr -> prev);
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
	if (ft_strncmp(str, "EOF", 3) == 0)
		return (TOKEN_EOF);
	else if (ft_strncmp((const char *)str, ">>", 2) == 0)
		return (TOKEN_APPEND);
	else if (ft_strncmp((const char *)str, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (str[0] == '>')
		return (TOKEN_REDIR_OUT);
	else if(str[0] == '<')
		return (TOKEN_REDIR_IN);
	else if (str[0] == '|')
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

t_token	*new_node(char *str, t_shell *shell)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new -> type = token_type(str);
	new -> value = ft_safe_strdup(str, shell);
	new -> prev = NULL;
	new -> next = NULL;
	return (new);
}

void	build_token_list(t_shell *shell, char **arr)
{
	t_token	*new;
	int		i;

	i = 0;
	// if (shell == NULL || arr == NULL)
	// 	return ;	exit and clean?
	while (arr[i] != NULL)
	{
		new = new_node(arr[i], shell);
		if (new == NULL)
			return (free_list(shell));
		append_node(shell, new);
		i++;
	}
	free_split_arr(arr);
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
// 	t_token *tokens;
// 	t_cmd	*cmds;
// 	char	**arr;

// 	tokens = NULL;
// 	cmds = NULL;
// 	arr = split("<< echo hello | wc -l >>> << outfile >>");
// 	build_token_list(&tokens, arr);
// 	//print_list(tokens);
//	free_list(shell);
// 	build_commands(&cmds, &tokens);
// 	print_cmds(&tokens, &cmds);
// }

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
// 			printf("REDIR=%s ; ", r->file);
// 			r = r->next;
// 		}
// 		curr = curr->next;
// 		printf("\nnext command\n");
// 	}
// 	free_list(shell);
// 	free(shell->line);
// 	free(shell);
// }