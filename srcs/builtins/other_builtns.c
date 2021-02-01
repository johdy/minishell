#include "minishell.h"

int		is_num(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int		print_num_arg_req(char *str)
{
	ft_putstr_fd("minibash: exit: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": numeric argument required\n", 1);
	return (255);
}

void	ft_exit(t_command *cmd, char **ms_environ, int *pipefd, char *bin)
{
	int exit_code;

	ft_putstr_fd("exit\n", 1);
	exit_code = 0;
	if (cmd->size > 1 && is_num(cmd->words[1]))
	{
		if (cmd->size > 2)
		{
			ft_putstr_fd("minibash: exit: too many arguments\n", 1);
			cmd->out = 1;
			return ;
		}
		else
			exit_code = ft_atoi(cmd->words[1]);
	}
	else if (cmd->size > 1)
		exit_code = print_num_arg_req(cmd->words[1]);
	clean_commands(&cmd);
	clean_path(ms_environ);
	free(pipefd);
	free(bin);
	system("leaks a.out");
	exit(exit_code);
}

int		ft_pwd(t_command *cmd)
{
	char *cwd;

	if (cmd->size > 1)
	{
		ft_putstr_fd("pwd: too many arguments\n", 1);
		cmd->out = 1;
		return (1);
	}
	if (!(cwd = getcwd(NULL, 0)))
		return (0);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (1);
}

void	ft_echo(t_command *cmd)
{
	int i;

	i = 1;
	if (!ft_strcmp(cmd->words[i], "-n"))
		i++;
	while (cmd->words[i])
	{
		ft_putstr_fd(cmd->words[i], 1);
		if (cmd->words[++i])
			ft_putstr_fd(" ", 1);
	}
	if (ft_strcmp(cmd->words[1], "-n"))
		ft_putstr_fd("\n", 1);
}
