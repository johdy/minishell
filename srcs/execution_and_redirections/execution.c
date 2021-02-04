/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:00:54 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:00:57 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_execve(char *bin, t_command *cmd, char ***ms_environ, int **fds)
{
	int *pipefd;
	int *fd_open;
	int ret;

	fd_open = fds[0];
	pipefd = fds[1];
	if (is_builtin(cmd->words[0]))
	{
		if (!ft_strcmp(cmd->words[0], "exit"))
		{
			clean_op_fd(fd_open, 1);
			restore_std(cmd->old_stdin, cmd->old_stdout);
		}
		ret = exec_builtin(cmd, ms_environ, pipefd, bin);
		return (ret);
	}
	free(fd_open);
	execve(bin, cmd->words, *ms_environ);
	return (0);
}

int		ft_execution(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	int			*fd_open;
	t_command	*redir;
	int			*fds[2];

	fd_open = NULL;
	if (!(fd_open = get_fd_redir(fd_open, cmd)))
		return (-12);
	if (fd_open[0] == -1 || fd_open[1] == -1 || fd_open[0] == -2)
		return (clean_op_fd(fd_open, 1));
	redir = cmd;
	while (is_redirection_cmd(redir->end_command) ||
		!ft_strcmp(redir->end_command, "PIPE"))
		redir = deal_redirection(pipefd, redir, fd_open);
	if (!bin && !is_builtin(cmd->words[0]))
	{
		print_cmd_not_found(cmd);
		return (clean_op_fd(fd_open, 1));
	}
	fds[0] = fd_open;
	fds[1] = pipefd;
	return (clean_op_fd(fd_open, ft_execve(bin, cmd, ms_environ, fds)));
}

int		forkit(char *bin, t_command *cmd, int *pipefd, char ***ms_environ)
{
	int		stt;

	g_sig.fork = fork();
	if (g_sig.fork == 0)
	{
		if (!ft_execution(bin, cmd, pipefd, ms_environ))
			print_exec_error(cmd);
		exit(127);
	}
	else if (g_sig.fork > 0)
		waitpid(g_sig.fork, &stt, 0);
	else
		return (0);
	if (WIFEXITED(stt))
		cmd->out = WEXITSTATUS(stt);
	if (g_sig.ret)
		cmd->out = g_sig.ret;
	g_sig.ret = 0;
	g_sig.fork = 0;
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

int		*execute_cmd(t_command *cmd, char ***ms_e, int *o_std, t_command **cmds)
{
	char	**path;
	char	*bin;
	int		*pipefd;
	int		error_exec;

	cmd->old_stdin = o_std[0];
	cmd->old_stdout = o_std[1];
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
	close(pipefd[0]);
	close(pipefd[1]);
	free(pipefd);
	return (NULL);
}
