#include "minishell.h"


t_command	*suppress_cmd(t_command *cmd, t_command *prev)
{
	t_command *cache;
	int i;

	i = 0;
	cache = cmd->next;
	free(prev->end_command);
	prev->end_command = ft_strdup(cmd->end_command);
	while (cmd->words[i])
		free(cmd->words[i++]);
	free(cmd->words);
	free(cmd->end_command);
	free(cmd->quotes);
	free(cmd->stickits);
	free(prev->next);
	prev->next = cache;
	return (prev);
}

t_command	*correct_multiple_arg_redir(t_command *cmd, t_command *cmd2)
{
	char **new_w_tb;
	int i;
	int j;

	i = 0;
	j = 1;
	new_w_tb = malloc(sizeof(char*) * (cmd->size + cmd2->size));
	while (cmd->words[i])
	{
		new_w_tb[i] = ft_strdup(cmd->words[i]);
		free(cmd->words[i++]);
	}
	while (cmd2->words[j])
	{
		new_w_tb[i + j - 1] = ft_strdup(cmd2->words[j]);
		cmd->size++;
		j++;
	}
	new_w_tb[i + j - 1] = NULL;
	free(cmd->words);
	cmd->words = new_w_tb;
	if (!ft_strcmp(cmd->end_command, "LOWER"))
		cmd2 = suppress_cmd(cmd2, cmd);
	return (cmd2);
}

void	correct_cmd(t_command *cmd)
{
	t_command *cmd2;

	lookfor_envvar(cmd);
	stick_words(cmd);
	cmd2 = cmd->next;
	while (cmd2 && is_redirection_cmd(cmd->end_command))
	{
		lookfor_envvar(cmd2);
		stick_words(cmd2);
		if (cmd2->size > 1)
			cmd = correct_multiple_arg_redir(cmd, cmd2);
		else
			cmd = cmd->next;
		cmd2 = cmd->next;
	}
}
