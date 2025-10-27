#include "minishell.h"

int	apply_redir(t_redir *redirection)
{
	t_redir	*r;
	int		fd;

	r = redirection;
	while (r != NULL)
	{
		if (r->type == TOKEN_REDIR_OUT)
			fd = open(r->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (r->type == TOKEN_APPEND)
			fd = open(r->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (r->type == TOKEN_REDIR_IN)
			fd = open(r->file, O_RDONLY);
		else if (r->type == TOKEN_HEREDOC)
			fd = handle_heredoc(r->file);
		if (fd == -1)
		{
			perror(r->file);
			exit(1);
		}
		if (r->type == TOKEN_REDIR_IN || r->type == TOKEN_HEREDOC)
			dup2(fd, STDIN_FILENO);
		if (r->type == TOKEN_REDIR_OUT || r->type == TOKEN_APPEND)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		r = r->next;
	}
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

char	*get_paths_from_env(t_env *env)
{
	t_env	*curr;

	curr = env;
	while (curr != NULL)
	{
		if (ft_strncmp(curr->name, "PATH=", 5) == 0)
			return (curr->value);
		curr = curr->next;
	}
}

char	**split_paths(char *paths_from_env)
{
	char	**all_paths;
	int		path_count;
	int		i;

	i = 0;
	path_count = 1;
	while (paths_from_env[i] != '\0')
	{
		if (paths_from_env[i] == ':')
			path_count++;
		i++;
	}
	all_paths = safe_calloc()
}

char	*path_lookup(t_cmd *cmd, char *path)
{
	char	**all_paths;
	char	*paths_from_env;

	paths_from_env = get_paths_from_env(cmd->env);
	all_paths = split_paths(paths_from_env);
}

int	exec_ext_cmd(t_cmd *cmd)
{
	pid_t	child;
	char	*path;	

	child = fork();
	if (child == -1)
	{
		perror("fork failure");
		return (1);
	}
	if (child == 0)
	{
		apply_redir(cmd->redir);
		if (is_direct_path(cmd->argv[0]) == true)
			path = cmd->argv[0];
		else
		{
			path = path_lookup(cmd, cmd->argv[0]);
		}
	}
}

int	exec_single_cmd(t_shell *shell)
{
	t_cmd	*cmd;

	cmd = shell->cmds;
	if (cmd->argv == NULL || cmd->argv[0] == NULL)
	{
		//no command;
		return (0);
	}
	if (is_builtin(cmd) == true)
	{
		return (exec_builtin(cmd));
	}
	return (exec_ext_cmd(cmd));
}