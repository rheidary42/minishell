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

void	clean_heredoc(char *tmp_file)
{
	write(1, "\n", 1);
	unlink(tmp_file);
	free(tmp_file);
	exit(130);
}

void	sig_handler(int sig)
{
	g_sig = sig;
}

void	run_heredoc(t_shell *shell, char *tmp_file, char *delim)
{
	char	*line;
	int		fd;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	fd = open(tmp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	while (1)
	{
		g_sig = 0;
		line = readline("heredoc> ");
		if (g_sig == SIGINT)
			clean_heredoc(tmp_file);
		if (line == NULL || ft_strcmp(line, delim) == 0)
			break;
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

int	handle_heredoc(t_shell *shell, char *delim)
{
	char	*tmp_file;
	pid_t	child;
	int		fd;
	int		status;

	tmp_file = get_here_doc_name(shell);
	child = fork();
	if (child == -1)
		return (-1);
	else if (child == 0)
		run_heredoc(shell, tmp_file, delim);
	waitpid(child, &status, 0);
	if (WIFSIGNALED(status) != 0 && WTERMSIG(status) == SIGINT)
	{
		shell->last_exit_status = 130;
		unlink(tmp_file);
		free(tmp_file);
		return (-1);
	}
	fd = open(tmp_file, O_RDONLY);
	unlink(tmp_file);
	free(tmp_file);
	return (fd);
}


// int	main(int ac, char **av)
// {
// 	t_shell *shell;
// 	handle_heredoc(shell, av[1]);
// 	return ;
// }