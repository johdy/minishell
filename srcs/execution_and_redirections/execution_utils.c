#include "minishell.h"

int		exec_builtin(t_command *cmd, char ***ms_environ, int *pipefd, char *bin)
{
	int ret;

	ret = 1;
	if (!ft_strcmp(cmd->words[0], "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd->words[0], "cd"))
		ret = ft_cd(cmd, *ms_environ);
	if (!ft_strcmp(cmd->words[0], "pwd"))
		ret = ft_pwd(cmd);
	if (!ft_strcmp(cmd->words[0], "exit"))
		ft_exit(cmd, *ms_environ, pipefd, bin);
	if (!ft_strcmp(cmd->words[0], "env"))
		ft_env(cmd, *ms_environ);
	if (!ft_strcmp(cmd->words[0], "unset"))
		ret = ft_unset(cmd, *ms_environ);
	if (!ft_strcmp(cmd->words[0], "export"))
		ret = ft_export(cmd, ms_environ);
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		exit(0);
	return (ret);
}

int		clean_op_fd(int *fd_open, int ret)
{
	if (fd_open[0] != 0 && fd_open[0] != -1)
		close(fd_open[0]);
	if (fd_open[1] != 1 && fd_open[1] != -1)
		close(fd_open[1]);
	free(fd_open);
	return (ret);
}

int		*get_fd_redir(int *fdo, t_command *cmd)
{
	t_command *redir;

	redir = cmd;
	if (!(fdo = malloc(sizeof(int) * 2)))
		return (NULL);
	fdo[0] = 0;
	fdo[1] = 1;
	while (is_redirection_cmd(redir->end_command)
		&& (fdo[0] >= 0 && fdo[1] >= 0))
	{
		fdo = how_to_open(redir->end_command, redir->next->words[0], fdo);
		if (fdo[0] == -1 || fdo[1] == -1)
			print_fd_error(redir, cmd);
		redir = redir->next;
	}
	return (fdo);
}
