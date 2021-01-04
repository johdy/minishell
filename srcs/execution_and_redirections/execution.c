#include "minishell.h"

void	fork_exec(char *bin, t_command *cmd, int *pipefd)
{
	int fd_open;

	fd_open = 1;
	if (is_redirection_cmd(cmd->end_command))
		fd_open = how_to_open(cmd->end_command, cmd->next->words[0]);
	if (fd_open < 0)
	{
		ft_putstr_fd(cmd->next->words[0], 0);
		ft_putstr_fd(": No such file or directory\n", 0);
		return ;
	}
	if (is_redirection_cmd(cmd->end_command) || !ft_strcmp(cmd->end_command, "PIPE"))
		deal_redirection(pipefd, cmd, fd_open);
	if (execve(bin, cmd->words, environ) < 0)
	{
		ft_putstr_fd(strerror(errno), 0);
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

	pipefd = malloc(sizeof(int) * 2);
	path = get_path();
	lookfor_envvar(cmd);
	stick_words(cmd);
//	printf("again.\n");
//	display_commands(&cmd);
	if (is_builtin(cmd->words[0]))
		return (exec_builtin(cmd));
	bin = get_bin(cmd->words[0], path);
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
	return (NULL);
}
