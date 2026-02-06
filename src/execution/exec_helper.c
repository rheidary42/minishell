#include "minishell.h"

void	free_func(char **to_free)
{
	int	i;

	i = 0;
	if (to_free == NULL)
		return ;
	while (to_free[i] != NULL)
	{
		free(to_free[i]);
		i++;
	}
	free(to_free);
}

void	free_and_close(t_shell *shell, t_cmd *cmd, t_exec *exec)
{
	// No more freeing of arena-allocated memory
	// Need Borkhuu to verify this
	int	ret;
	(void)shell;
	(void)cmd;
	// all_paths, argv, final_path are arena-allocated; no need to free them
	ret = shell->last_exit_status;
	if (exec->pipe_fds[0] != -1)
	{
		close(exec->pipe_fds[0]);
		exec->pipe_fds[0] = -1;
	}
	if (exec->pipe_fds[1] != -1)
	{
		close(exec->pipe_fds[1]);
		exec->pipe_fds[1] = -1;
	}
	if (exec->file_fd != -1)
	{
		close(exec->file_fd);
		exec->file_fd = -1;
	}
	free(shell->arena);
	free_env_list(shell->env);
	free(shell);
	exit(ret);
}

void	initialise_exec(t_exec *exec)
{
	ft_memset(exec, 0, sizeof(t_exec));
	exec->prev_fd = -1;
	exec->pipe_fds[0] = -1;
	exec->pipe_fds[1] = -1;
	exec->file_fd = -1;
}

bool	is_direct_path(char *executable)
{
	int	i;

	i = 0;
	while (executable[i] != '\0')
	{
		if (executable[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

char	*str_join3(char *s1, char *s2, char *s3, t_shell *shell)
{
	char	*str_comb;
	int		a;
	int		b;
	int		c;

	str_comb = (char *)arena_push(shell->arena, ft_strlen(s1) + ft_strlen(s2)
			+ ft_strlen(s3) + 1, 0, shell);
	a = 0;
	b = 0;
	c = 0;
	while (s1[a] != '\0')
	{
		str_comb[a] = s1[a];
		a++;
	}
	while (s2[b] != '\0')
	{
		str_comb[a + b] = s2[b];
		b++;
	}
	while (s3[c] != '\0')
	{
		str_comb[a + b + c] = s3[c];
		c++;
	}
	str_comb[a + b + c] = '\0';
	return (str_comb);
}
