#include "minishell.h"

void	display_lex(t_list **lex)
{
	t_list *item;

	item = *lex;
	while (item)
	{
		printf("%s\n", item->content);
		item = item->next;
	}
}

void	display_commands(t_command **commands)
{
	t_command *cmd;
	int i;
	int count;
	int j;

	count = 0;
	cmd = *commands;
	while (cmd)
	{
		j = -1;
		printf("euh\n");
		printf("command %d of size %d\n", count, cmd->size);
		i = 0;
		while (cmd->words[i])
			printf("%s\n", cmd->words[i++]);
		printf("end command : %s\n", cmd->end_command);
		while (cmd->quotes[++j] != -1)
			printf("mot nb %d est quoted : %d\n", j, cmd->quotes[j]);
		j = -1;
		while (cmd->stickits[++j] != -1)
			printf("mot nb %d est stické : %d\n", j, cmd->stickits[j]);
		cmd = cmd->next;
		count++;
	}
}