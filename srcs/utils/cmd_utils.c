#include "minishell.h"

int		check_redir_pipe(t_command *cmd)
{
	while (cmd && is_redirection_cmd(cmd->end_command))
		cmd = cmd->next;
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		return (1);
	return (0);
}

void	print_cmd_not_found(t_command *cmd, char **ms_environ)
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
	char *test;
	
	printf("%p\n", redir);
	printf("%p\n", cmd);
	restore_std(cmd->old_stdin, cmd->old_stdout);
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(redir->next->words[0], 1);
	ft_putstr_fd(": ", 1);
	ft_putstr_fd(strerror(errno), 1);
	ft_putstr_fd("\n", 1);
	get_next_line(0, &test);
	errno = 113;
}
