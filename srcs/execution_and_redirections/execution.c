#include "minishell.h"

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

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

int		clean_op_fd(int *fd_open)
{
	if (fd_open[0] != 0)
		close (fd_open[0]);
	if (fd_open[1] != 1)
		close (fd_open[1]);
	free(fd_open);
	return (0);	
}

int		ft_execution(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	int *fd_open;
	t_command *redir;

	redir = cmd;
	fd_open = malloc(sizeof(int) * 2);
	fd_open[0] = 0;
	fd_open[1] = 1;
	while (is_redirection_cmd(redir->end_command) && (fd_open[0] >= 0 || fd_open[1] >= 0))
	{
		fd_open = how_to_open(redir->end_command, redir->next->words[0], fd_open);
		redir = redir->next;
	}
	redir = cmd;
	if (fd_open[0] < 0 || fd_open[1] < 0)
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	while (is_redirection_cmd(redir->end_command))
	{
		deal_redirection(pipefd, redir, fd_open);
		redir = redir->next;
	}
	if (!ft_strcmp(redir->end_command, "PIPE") && fd_open[1] == 1)
		deal_redirection(pipefd, redir, fd_open);
//	else if (!ft_strcmp(redir->end_command, "PIPE"))
//		old_fds = deal_redirection(pipefd, cmd, fd_open, old_fds);
	if (is_builtin(cmd->words[0]))
		exec_builtin(cmd, ms_environ, pipefd, bin);
	else if (execve(bin, cmd->words, *ms_environ) < 0)
		return (clean_op_fd(fd_open));
	clean_op_fd(fd_open);
	return (1);
}

void	cmd_not_found(t_command *cmd, char **ms_environ)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd->words[0], 1);
	ft_putstr_fd(": ", 1);
	restore_std(cmd->old_stdin, cmd->old_stdout);
	ft_putstr_fd("command not found\n", 1);
}

int		forkit(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	pid_t p_pid;
	int stt;

	p_pid = fork();
	if (p_pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (!bin && !is_builtin(cmd->words[0]))
			cmd_not_found(cmd, *ms_environ);
		else if (!ft_execution(bin, cmd, pipefd, ms_environ))
		{
			ft_putstr_fd("minishell: ", 1);
			ft_putstr_fd(cmd->words[0], 1);
			ft_putstr_fd(": ", 1);
			restore_std(cmd->old_stdin, cmd->old_stdout);
			ft_putstr_fd(strerror(errno), 1);
			ft_putstr_fd("\n", 1);
		}
		exit(127);
	}
	else if (p_pid > 0)
	{
		signal(SIGINT, sigc_fork);
		signal(SIGQUIT, sigbs_fork);
		
		waitpid(p_pid, &stt, 0);	
	}
	else
		return (0);
	if (WIFEXITED(stt))
		cmd->out = WEXITSTATUS(stt);
	signal(SIGINT, sigc);
	signal(SIGQUIT, sigbs);
	return (1);
}

int		check_redir_pipe(t_command *cmd)
{
	while (cmd && is_redirection_cmd(cmd->end_command))
		cmd = cmd->next;
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		return (1);
	return (0);
}

int		*execute_cmd(t_command *cmd, char ***ms_e, int *old_stds, t_command **cmds)
{
	char **path;
	char *bin;
	int *pipefd;

	cmd->old_stdin = old_stds[0];
	cmd->old_stdout = old_stds[1];
	path = get_path(*ms_e, cmds);
	crct_cmd(cmd, *ms_e, cmds, path);
	bin = get_bin(cmd->words[0], path, *ms_e, cmds);
	clean_path(path);
	if (!(pipefd = malloc(sizeof(int) * 2)) || pipe(pipefd))
		ft_failed_pipe(*ms_e, cmds);
	if (is_builtin(cmd->words[0]) && !check_redir_pipe(cmd))
		ft_execution(bin, cmd, pipefd, ms_e);
	else
	{
		if (!(forkit(bin, cmd, pipefd, ms_e)))
			ft_failed_fork(*ms_e, cmds, pipefd);
	}
	free(bin);
	if (check_redir_pipe(cmd))
		return (pipefd);
	else
		restore_std(cmd->old_stdin, cmd->old_stdout);
	close(pipefd[0]);
	close(pipefd[1]);
	free(pipefd);
	return (NULL);
}
