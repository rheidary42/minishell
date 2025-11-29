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
	free_func(exec->all_paths);
	free_func(cmd->argv);
	free(exec->final_path);
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

	str_comb = safe_calloc((ft_strlen(s1) + ft_strlen(s2)
				+ ft_strlen(s3) + 1), shell);
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
