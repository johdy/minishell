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

int		ft_execution(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	int fd_open;

	fd_open = 1;
	if (is_redirection_cmd(cmd->end_command))
		fd_open = how_to_open(cmd->end_command, cmd->next->words[0]);
	if (fd_open < 0)
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	if (is_redirection_cmd(cmd->end_command) || !ft_strcmp(cmd->end_command, "PIPE"))
		deal_redirection(pipefd, cmd, fd_open);
	if (is_builtin(cmd->words[0]))
		exec_builtin(cmd, ms_environ, pipefd, bin);
	else if (execve(bin, cmd->words, *ms_environ) < 0)
		return (0);
	return (1);
}

void	forkit(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	pid_t p_pid;
	int stt;

	p_pid = fork();
	if (p_pid == 0)
	{
		if (!ft_execution(bin, cmd, pipefd, ms_environ))
		{
			restore_std(cmd->old_stdin, cmd->old_stdout);
			ft_putstr_fd(strerror(errno), 1);
			ft_putstr_fd("\n", 1);
		}
		exit(0);
	}
	else if (p_pid > 0)
		waitpid(p_pid, &stt, 0);	
}

int		*execute_cmd(t_command *cmd, char ***ms_environ, int old_stdin, int old_stdout)
{
	char **path;
	char *bin;
	int *pipefd;

	path = get_path(*ms_environ);
	correct_cmd(cmd, *ms_environ);
	bin = get_bin(cmd->words[0], path);
	clean_path(path);
	cmd->old_stdin = old_stdin;
	cmd->old_stdout = old_stdout;
	pipefd = malloc(sizeof(int) * 2);
	pipe(pipefd);
	if (is_builtin(cmd->words[0]) && ft_strcmp(cmd->end_command, "PIPE"))
		ft_execution(bin, cmd, pipefd, ms_environ);
	else
		forkit(bin, cmd, pipefd, ms_environ);
	free(bin);
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		return (pipefd);
	else
		restore_std(old_stdin, old_stdout);
	free(pipefd);
	return (NULL);
}
