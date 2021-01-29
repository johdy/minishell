#include "minishell.h"

t_command	*deal_next_link(t_command *cmd)
{
	int redirected;

	redirected = 0;
	while (cmd && is_redirection_cmd(cmd->end_command))
	{
		redirected = 1;
		cmd->next->prev_out = cmd->out;
		cmd = cmd->next;
	}
	if (ft_strcmp(cmd->end_command, "END"))
	{
		cmd->next->prev_out = cmd->out;
		return (cmd->next);
	}
	else if (redirected)
		cmd->abort = 1;
	return (cmd);
}

void		connect_pipe(int *pipefd, int *old_stds)
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
		old_stds[0] = dup(0);
		old_stds[1] = dup(1);
	}
}

int			deal_cmd(t_command **commands, char ***ms_environ)
{
	t_command	*cmd;
	int			*pipefd;
	int			fd_open;
	int			old_stds[2];

	pipefd = NULL;
	cmd = *commands;
	while (cmd)
	{
		printf("%s\n", cmd->end_command);
		if (cmd->size && !cmd->abort)
		{
			connect_pipe(pipefd, old_stds);
			pipefd = execute_cmd(cmd, ms_environ, old_stds, commands);
		}
		if (!ft_strcmp(cmd->end_command, "END"))
			break ;
		cmd = deal_next_link(cmd);
	}
	return (cmd->out);
}

void		main_loop(char ***ms_environ, char **tojoin, int *init_prev_out)
{
	char		*line;
	int			err;
	t_list		*lex;
	t_command	*commands;

	if (!(*tojoin))
		ft_putstr_fd("minishell > ", 1);
	err = get_next_line(0, &line);
	if (!line)
		err = get_next_line(3, &line);
	if (err == 0)
		*tojoin = deal_ctrld(*tojoin, line, *ms_environ);
	else
	{
		if (*tojoin)
		{
			insert_in_new_input(&line, *tojoin, *ms_environ);
			*tojoin = NULL;
		}
		get_lex(line, &lex, *ms_environ);
		//display_lex(&lex);
		if (!get_commands(lex, &commands,*ms_environ))
			ft_failed_malloc(*ms_environ, &commands, &lex, 0);
		commands->prev_out = *init_prev_out;
		//display_commands(&commands);
		ft_lstclear(&lex, &free);
		*init_prev_out = deal_cmd(&commands, ms_environ);
		clean_commands(&commands);
	}
}

int		main(void)
{
	char	*tojoin;
	char	**ms_environ;
	int		init_prev_out;

	ms_environ = init_env();
	tojoin = NULL;
	signal(SIGINT, sigc);
	signal(SIGQUIT, sigbs);
	init_prev_out = 0;
	while (1)
		main_loop(&ms_environ, &tojoin, &init_prev_out);
}
