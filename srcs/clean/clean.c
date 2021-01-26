#include "minishell.h"

void	clean_cmd(t_command *cmd)
{
	int i;

	if (cmd->nb_malloc > 0)
		free(cmd->stickits);
	if (cmd->nb_malloc > 1)
		free(cmd->quotes);
	if (cmd->nb_malloc > 2)
	{
		i = 0;
		while (cmd->words[i])
			free(cmd->words[i++]);
		free(cmd->words);
	}
	if (cmd->nb_malloc > 3)
		free(cmd->end_command);
}

void	clean_commands(t_command **cmds)
{
	t_command *cmd;
	t_command *cache;

	cmd = *cmds;
	while (cmd)
	{
		clean_cmd(cmd);
		cache = cmd->next;
		free(cmd);
		cmd = cache;
	}
}

void	clean_path(char **path)
{
	int i;

	i = 0;
	while (path && path[i])
		free(path[i++]);
	if (path)
		free(path);
}

void	ft_failed_malloc(char **ms_environ, t_command **commands, t_list **lex, char *str)
{
	if (ms_environ)
		clean_path(ms_environ);
	if (commands)
		clean_commands(commands);
	if (lex)
		ft_lstclear(lex, &free);
	if (str)
		free(str);
	ft_putstr_fd("minishell: malloc failiure. exiting\n", 1);
	system("leaks a.out");
	exit(12);
}