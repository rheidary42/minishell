#include "minishell.h"

void	print_list(t_token *tokens)
{
	while (tokens != NULL)
	{
		printf("%s ; ", tokens -> value);
		printf("%i ; ", tokens -> type);
		printf("%p\n", tokens -> prev);
		tokens = tokens -> next;
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

void	free_list(t_token **head)
{
	t_token	*curr;
	t_token	*onebehind;

	if (head == NULL)
		return ;
	curr = *head;
	while (curr != NULL)
	{
		onebehind = curr;
		curr = curr -> next;
		free(onebehind -> value);
		free(onebehind);
	}
	*head = NULL;
}

void	append_node(t_token **tokens, t_token *new)
{
	t_token	*curr;

	if (tokens == NULL || new == NULL)
		return ;
	curr = *tokens;
	if (*tokens == NULL)
	{
		*tokens = new;
		return ;
	}
	while (curr -> next != NULL)
		curr = curr -> next;
	curr -> next = new;
	new -> prev = curr;
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

t_token	*new_node(char *str)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (NULL);
	new -> type = token_type(str);
	new -> value = ft_strdup(str);
	new -> prev = NULL;
	new -> next = NULL;
	return (new);
}

void	build_token_list(t_token **tokens, char **arr)
{
	t_token	*new;
	int		i;

	i = 0;
	if (tokens == NULL || arr == NULL)
		return ;
	while (arr[i] != NULL)
	{
		new = new_node(arr[i]);
		if (new == NULL)
			return (free_list(tokens));
		append_node(tokens, new);
		i++;
	}
	free_split_arr(arr);
	append_node(tokens, new_node("EOF"));
}
//TEST TOKENIZER
int	main(void)
{
	t_token *tokens;
	char	**arr;

	tokens = NULL;
	arr = split("<< echo hello | wc -l >>> << outfile >>");
	build_token_list(&tokens, arr);
	print_list(tokens);
	free_list(&tokens);
}