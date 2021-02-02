/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:01:05 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:01:06 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (fd_open[0] > 0)
		close(fd_open[0]);
	if (fd_open[1] != 1 && fd_open[1] > -1)
		close(fd_open[1]);
	free(fd_open);
	return (ret);
}

void	print_unexpected_token(t_command *cmd, int *fdo)
{
	restore_std(cmd->old_stdin, cmd->old_stdout);
	ft_putstr_fd("minishell: syntax error ", 1);
	ft_putstr_fd("near unexpected token 'newline'\n", 1);
	errno = 113;
	cmd->out = 258;
	fdo[0] = -2;
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
		if (!redir->next->words[0])
		{
			print_unexpected_token(cmd, fdo);
			break ;
		}
		fdo = how_to_open(redir->end_command, redir->next->words[0], fdo);
		if (fdo[0] == -1 || fdo[1] == -1)
			print_fd_error(redir, cmd);
		redir = redir->next;
	}
	return (fdo);
}

void	wait_for_it(int *stt, pid_t p_pid)
{
	signal(SIGINT, sigc_fork);
	signal(SIGQUIT, sigbs_fork);
	waitpid(p_pid, stt, 0);
}
