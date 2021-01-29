#include "minishell.h"

void	exec_builtin(t_command *cmd, char ***ms_environ, int *pipefd, char *bin)
{	
	if (!ft_strcmp(cmd->words[0], "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd->words[0], "cd"))
		ft_cd(cmd, *ms_environ);
	if (!ft_strcmp(cmd->words[0], "pwd"))
		ft_pwd(cmd);
	if (!ft_strcmp(cmd->words[0], "exit"))
		ft_exit(cmd, *ms_environ, pipefd, bin);
	if (!ft_strcmp(cmd->words[0], "env"))
		ft_env(cmd, *ms_environ);
	if (!ft_strcmp(cmd->words[0], "unset"))
		ft_unset(cmd, *ms_environ);
	if (!ft_strcmp(cmd->words[0], "export"))
		ft_export(cmd, ms_environ);
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		exit(0);
}

int		clean_op_fd(int *fd_open, int ret)
{
	if (fd_open[0] != 0 && fd_open[0] != -1)
		close (fd_open[0]);
	if (fd_open[1] != 1)
		close (fd_open[1] && fd_open[0] != -1);
	free(fd_open);
	return (ret);	
}

int		*get_fd_redir(int *fd_open, t_command *cmd)
{
	t_command *redir;

	redir = cmd;
	if (!(fd_open = malloc(sizeof(int) * 2)))
		return (NULL);
	fd_open[0] = 0;
	fd_open[1] = 1;
	while (is_redirection_cmd(redir->end_command) && (fd_open[0] >= 0 || fd_open[1] >= 0))
	{
		fd_open = how_to_open(redir->end_command, redir->next->words[0], fd_open);
		if (fd_open[0] == -1 || fd_open[1] == -1)
			print_fd_error(redir, cmd);
		redir = redir->next;
	}
	return (fd_open);
}

int		ft_execution(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	int *fd_open;
	t_command *redir;
	char *test;

	if (!(fd_open = get_fd_redir(fd_open, cmd)))
		return (-12);
	if (fd_open[0] == -1 || fd_open[1] == -1)
		return (clean_op_fd(fd_open, 1));
	redir = cmd;
	while (is_redirection_cmd(redir->end_command))
	{
		deal_redirection(pipefd, redir, fd_open);
		redir = redir->next;
	}
	if (!ft_strcmp(redir->end_command, "PIPE") && fd_open[1] == 1)
		deal_redirection(pipefd, redir, fd_open);
//	else if (!ft_strcmp(redir->end_command, "PIPE"))
//		old_fds = deal_redirection(pipefd, cmd, fd_open, old_fds);
	if (!bin && !is_builtin(cmd->words[0]))
	{
		print_cmd_not_found(cmd, *ms_environ);
		return (clean_op_fd(fd_open, 1));
	}
	if (is_builtin(cmd->words[0]))
		exec_builtin(cmd, ms_environ, pipefd, bin);
	else if (execve(bin, cmd->words, *ms_environ) < 0)
		return (clean_op_fd(fd_open, 0));
	return (clean_op_fd(fd_open, 1));
}

int		forkit(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	pid_t p_pid;
	int stt;

	p_pid = fork();
	if (p_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!ft_execution(bin, cmd, pipefd, ms_environ))
			print_exec_error(cmd);
		exit(127);
	}
	else if (p_pid > 0)
		wait_for_it(&stt, p_pid);
	else
		return (0);
	if (WIFEXITED(stt))
		cmd->out = WEXITSTATUS(stt);
	signal(SIGINT, sigc);
	signal(SIGQUIT, sigbs);
	return (1);
}

int		launch_execution(t_command *cmd, char *bin, char ***ms_e, int *pipefd)
{
	int err_nb;

	if (is_builtin(cmd->words[0]) && !check_redir_pipe(cmd))
	{
		err_nb = ft_execution(bin, cmd, pipefd, ms_e);
		if (err_nb < 0)
			return (err_nb);
	}
	else
	{
		if (!(forkit(bin, cmd, pipefd, ms_e)))
			return (-1);
	}
	free(bin);
	return (0);
}

int		*execute_cmd(t_command *cmd, char ***ms_e, int *old_stds, t_command **cmds)
{
	char **path;
	char *bin;
	int *pipefd;
	int error_exec;

	printf("%d\n", cmd->error_exit);
	cmd->old_stdin = old_stds[0];
	cmd->old_stdout = old_stds[1];
	path = get_path(*ms_e, cmds);
	crct_cmd(cmd, *ms_e, cmds, path);
	bin = get_bin(cmd->words[0], path, *ms_e, cmds);
	clean_path(path);
	if (!(pipefd = malloc(sizeof(int) * 2)))
		ft_failed_malloc(*ms_e, cmds, 0, 0);
	if (pipe(pipefd))
		ft_failed_what(*ms_e, cmds, 0, 1);
	if ((error_exec = launch_execution(cmd, bin, ms_e, pipefd)))
		ft_failed_what(*ms_e, cmds, pipefd, error_exec);
	if (check_redir_pipe(cmd))
		return (pipefd);
	else if (errno != 113)
		restore_std(cmd->old_stdin, cmd->old_stdout);
	printf("%d\n", errno);
	close(pipefd[0]);
	close(pipefd[1]);
	free(pipefd);
	return (NULL);
}
