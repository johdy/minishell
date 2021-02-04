/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdyer <jdyer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:02:15 by jdyer             #+#    #+#             */
/*   Updated: 2021/02/02 11:02:18 by jdyer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_redir_pipe(t_command *cmd)
{
	while (cmd && is_redirection_cmd(cmd->end_command))
		cmd = cmd->next;
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		return (1);
	return (0);
}

void	print_cmd_not_found(t_command *cmd)
{
	restore_std(cmd->old_stdin, cmd->old_stdout);
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd->words[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd("command not found\n", 1);
	errno = 113;
}

void	print_exec_error(t_command *cmd)
{
	restore_std(cmd->old_stdin, cmd->old_stdout);
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(cmd->words[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
	errno = 113;
}

void	print_fd_error(t_command *redir, t_command *cmd)
{
	restore_std(cmd->old_stdin, cmd->old_stdout);
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(redir->next->words[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
	errno = 113;
}

int		print_syntax_error(t_command *cmd, t_command *first)
{
	ft_putstr_fd("minishell: syntax error ", 1);
	ft_putstr_fd("near unexpected token ", 1);
	if (!ft_strcmp(cmd->end_command, "GREATER"))
		ft_putstr_fd("'>'\n", 1);
	if (!ft_strcmp(cmd->end_command, "LOWER"))
		ft_putstr_fd("'<'\n", 1);
	if (!ft_strcmp(cmd->end_command, "DGREATER"))
		ft_putstr_fd("'>>'\n", 1);
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		ft_putstr_fd("'|'\n", 1);
	if (!ft_strcmp(cmd->end_command, "SC"))
		ft_putstr_fd("';'\n", 1);
	if (!ft_strcmp(cmd->end_command, "END"))
		ft_putstr_fd("'newline'\n", 1);
	first->out = 258;
	return (1);
}
