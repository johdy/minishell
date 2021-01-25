#include "minishell.h"

void	clean_commands(t_command **cmds)
{
	int i;

	t_command *cmd;
	t_command *cache;
	cmd = *cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->words[i])
			free(cmd->words[i++]);
		free(cmd->words);
		free(cmd->end_command);
		free(cmd->quotes);
		free(cmd->stickits);
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

void	ft_failed_malloc(char **ms_environ, t_command **commands)
{
	if (ms_environ)
		clean_path(ms_environ);
	if (commands)
		clean_commands(commands);
	ft_putstr_fd("minishell : malloc failiure. exiting\n", 1);
	system("leaks a.out");
	exit(12);
}