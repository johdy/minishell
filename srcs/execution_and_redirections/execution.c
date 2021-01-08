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

void	exec_builtin(t_command *cmd)
{	
	if (!ft_strcmp(cmd->words[0], "echo"))
		ft_echo(cmd);
	if (!ft_strcmp(cmd->words[0], "cd"))
		ft_cd(cmd);
	if (!ft_strcmp(cmd->words[0], "pwd"))
		ft_pwd(cmd);
}

void	fork_exec(char *bin, t_command *cmd, int *pipefd)
{
	int fd_open;

	fd_open = 1;
	if (is_redirection_cmd(cmd->end_command))
		fd_open = how_to_open(cmd->end_command, cmd->next->words[0]);
	if (fd_open < 0)
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 0);
		return ;
	}
	if (is_redirection_cmd(cmd->end_command) || !ft_strcmp(cmd->end_command, "PIPE"))
		deal_redirection(pipefd, cmd, fd_open);
	if (is_builtin(cmd->words[0]))
		exec_builtin(cmd);
	else if (execve(bin, cmd->words, environ) < 0)
	{
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 0);
	}
}

int		*execute_cmd(t_command *cmd)
{
	pid_t p_pid;
	int stt;
	char **path;
	char *bin;
	int *pipefd;

	path = get_path();
	correct_cmd(cmd);
//	printf("again.\n");
//	display_commands(&cmd);
	bin = get_bin(cmd->words[0], path);
	pipefd = malloc(sizeof(int) * 2);
	pipe(pipefd);
	p_pid = fork();
	if (p_pid == 0)
		fork_exec(bin, cmd, pipefd);
	else if (p_pid > 0)
		waitpid(p_pid, &stt, 0);
	clean_path(path);
	free(bin);
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		return (pipefd);
	free(pipefd);
	return (NULL);
}
