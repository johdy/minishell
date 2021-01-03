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
}
