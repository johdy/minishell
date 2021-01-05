#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int		deal_cmd(t_command **commands)
{
	t_command *cmd;
	int *pipefd;
	int fd_open;

	pipefd = NULL;
	cmd = *commands;
	while(cmd)
	{
		if (cmd->size)
		{
			if (pipefd)
			{
				close(pipefd[1]);
				dup2(pipefd[0], 0);
				close(pipefd[0]);				
			}
			pipefd = execute_cmd(cmd);
		}
		if (is_redirection_cmd(cmd->end_command))
			cmd = cmd->next;
		cmd = cmd->next;
	}
	return (1);
}

int		main(void)
{
	char *line;
	int err;
	t_list *lex;
	t_command *commands;
	int old_stdin;
	int	old_stdout;

	while (1)
	{
		old_stdin = dup(0);
		old_stdout = dup(1);
		//printf("%d %d\n", old_stdin, old_stdout);
		ft_putstr_fd("miniwouf > ", 1);
		err = get_next_line(0, &line);
		get_lex(line, &lex);
		//display_lex(&lex);
		get_commands(lex, &commands);
		//display_commands(&commands);
		ft_lstclear(&lex, &free);
		deal_cmd(&commands);
		clean_commands(&commands);
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
		close(old_stdin);
		close(old_stdout);
	}
}