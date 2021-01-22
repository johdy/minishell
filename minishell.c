#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

char	**init_env(void)
{
	char **ret;
	int size;
	int i;

	i = 0;
	size = 0;
	while(environ[size])
		size++;
	ret = malloc(sizeof(char*) * (size + 1));
	while (i < size)
	{
		ret[i] = ft_strdup(environ[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

int		deal_cmd(t_command **commands, char ***ms_environ)
{
	t_command *cmd;
	int *pipefd;
	int fd_open;
	int old_stdin;
	int	old_stdout;

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
				free(pipefd);
			}
			else
			{
				old_stdin = dup(0);
				old_stdout = dup(1);
			}
			pipefd = execute_cmd(cmd, ms_environ, old_stdin, old_stdout);
			//printf("%d printf%d\n", pipefd[0], pipefd[1]);
		}
		while (cmd && is_redirection_cmd(cmd->end_command))
		{
			cmd->next->prev_out = cmd->out;
			cmd = cmd->next;
		}
		if (ft_strcmp(cmd->end_command, "END"))
		{
			cmd->next->prev_out = cmd->out;
			cmd = cmd->next;
		}
		else
			break;
	}
	return (cmd->out);
}

int		main(void)
{
	char *tojoin;
	char *line;
	int err;
	t_list *lex;
	t_command *commands;
	char	**ms_environ;
	int		init_prev_out;

	ms_environ = init_env();
	tojoin = NULL;
    signal(SIGINT, sigc);
    signal(SIGQUIT, sigbs);
    init_prev_out = 0;
	while (1)
	{
		if (!tojoin)
			ft_putstr_fd("miniwouf > ", 1);
		err = get_next_line(0, &line);
		if (err == 0)
			tojoin = deal_ctrld(tojoin, line, ms_environ);
		else
		{
			if (tojoin)
			{
				insert_in_new_input(&line, tojoin);
				tojoin = NULL;
			}
			get_lex(line, &lex);
			//display_lex(&lex);
			get_commands(lex, &commands);
			commands->prev_out = init_prev_out;
			//display_commands(&commands);
			ft_lstclear(&lex, &free);
			init_prev_out = deal_cmd(&commands, &ms_environ);
			clean_commands(&commands);
		}
	}
}