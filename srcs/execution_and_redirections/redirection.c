#include "minishell.h"

int		*how_to_open(char *redir, char *file, int *fd_open)
{
	if (!ft_strcmp(redir, "LOWER"))
		fd_open[0] = open(file, O_RDONLY, 777);
	else if (!ft_strcmp(redir, "GREATER"))
		fd_open[1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else
		fd_open[1] = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	return (fd_open);
}

int		*deal_redirection(int *pipefd, t_command *cmd, int *fd_open, int *old_fds)
{
	int fsti;
	int fsto;

	if (!old_fds)
	{
		old_fds = malloc(sizeof(int) * 2);
		old_fds[0] = 0;
		old_fds[1] = 1;
	}
	if (!ft_strcmp(cmd->end_command, "PIPE"))
	{
		printf("ola\n");
		close(pipefd[0]); /* close the unused read side */
		dup2(pipefd[1], 1); /* connect the write side with stdout */
		close(pipefd[1]); /* close the write side */
		return (old_fds);
	}
	if (!ft_strcmp(cmd->end_command, "LOWER") && fd_open > 0)
	{
		dup2(fd_open[0], old_fds[0]);
		//close(old_fds[0]);
		old_fds[0] = fd_open[0];
	}
	else if (fd_open > 0)
	{
		dup2(fd_open[1], old_fds[1]);
		//close(old_fds[1]);
		old_fds[1] = fd_open[1];
	}
	return (old_fds);
}
