#include "minishell.h"

int		*how_to_open(char *redir, char *file, int *fd_open)
{
	if (!ft_strcmp(redir, "LOWER"))
	{
		if (fd_open[0] != 0)
			close(fd_open[0]);
		fd_open[0] = open(file, O_RDONLY, 777);
	}
	else if (!ft_strcmp(redir, "GREATER"))
	{
		if (fd_open[1] != 1)
			close(fd_open[1]);		
		fd_open[1] = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	}
	else
	{
		if (fd_open[1] != 1)
			close(fd_open[1]);
		fd_open[1] = open(file, O_WRONLY | O_APPEND | O_CREAT, 0777);
	}
	return (fd_open);
}

void	deal_redirection(int *pipefd, t_command *cmd, int *fd_open)
{
	int fsti;
	int fsto;

	if (!ft_strcmp(cmd->end_command, "PIPE"))
	{
		close(pipefd[0]); /* close the unused read side */
		dup2(pipefd[1], 1); /* connect the write side with stdout */
		close(pipefd[1]); /* close the write side */
		return ;
	}
	if (!ft_strcmp(cmd->end_command, "LOWER") && fd_open[0] > 0)
		dup2(fd_open[0], 0);
	else if (ft_strcmp(cmd->end_command, "LOWER") && fd_open[1] > 0)
		dup2(fd_open[1], 1);
	return ;
}
