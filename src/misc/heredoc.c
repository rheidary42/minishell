#include "minishell.h"

char	*get_here_doc_name(t_shell *shell)
{
	static int	heredoc_idx;
	char		*idx_str;
	char		*tmp_name;

	idx_str = ft_itoa(heredoc_idx++);
	if (idx_str == NULL)
		return (clean_up(shell), NULL);
	tmp_name = str_join3("/tmp/heredoc_", "\0", idx_str, shell);
	free(idx_str);
	return (tmp_name);
}

int	run_heredoc(t_shell *shell, char *tmp_file, char *delim)
{
	char	*line;
	int		fd;
	// void(*old_sigint)(int);
	// void(*old_sigquit)(int);

	// old_sigint = signal(SIGINT, heredoc_sig_handler);
	// old_sigquit = signal(SIGQUIT, SIG_IGN);
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			free(line);
			close(fd);
			// signal(SIGINT, old_sigint);
			// signal(SIGQUIT, old_sigquit);
			printf("HI");
			return (130);
		}
		if (line == NULL || ft_strcmp(line, delim) == 0  || g_sig == SIGINT)
		{
			printf("NOT HI");

			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

int	heredoc_collector(t_shell *shell)
{
	t_cmd	*cmd;
	t_redir	*r;
	char	*tmp;

	cmd = shell->cmds;
	while (cmd != NULL)
	{
		r = cmd->redir;
		while (r != NULL)
		{
			if (r->type == TOKEN_HEREDOC)
			{
				tmp = get_here_doc_name(shell);
				if (run_heredoc(shell, tmp, r->file) == 130)
				{
					unlink(tmp);
					// free(tmp);
					return (1);
				}
				r->file = tmp; // arena free?
			}
			r = r->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
