#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int		is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int		*exec_builtin(t_command *cmd)
{
	return (NULL);
}

int		how_to_open(char *redir, char *file)
{
	if (!ft_strcmp(redir, "LOWER"))
		return (open(file, O_RDONLY, 777));
	else if (!ft_strcmp(redir, "GREATER"))
		return (open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777));
	else
		return (open(file, O_WRONLY | O_APPEND | O_CREAT, 0777));
}

void	deal_redirection(int *pipefd, t_command *cmd, int fd_open)
{
	if (!ft_strcmp(cmd->end_command, "PIPE"))
	{
		close(pipefd[0]); /* close the unused read side */
		dup2(pipefd[1], 1); /* connect the write side with stdout */
		close(pipefd[1]); /* close the write side */
		return ;
	}
	if (!ft_strcmp(cmd->end_command, "LOWER") &&  fd_open > 0)
		dup2(fd_open, 0);
	else if (fd_open > 0)
		dup2(fd_open, 1);
	return ;
}

void	fork_exec(char *bin, t_command *cmd, int *pipefd)
{
	int fd_open;

	fd_open = 1;
	if (is_redirection_cmd(cmd->end_command))
		fd_open = how_to_open(cmd->end_command, cmd->next->words[0]);
	if (fd_open < 0)
	{
		ft_putstr_fd(cmd->next->words[0], 0);
		ft_putstr_fd(": No such file or directory\n", 0);
		return ;
	}
	if (is_redirection_cmd(cmd->end_command) || !ft_strcmp(cmd->end_command, "PIPE"))
		deal_redirection(pipefd, cmd, fd_open);
	if (execve(bin, cmd->words, environ) < 0)
	{
		ft_putstr_fd(strerror(errno), 0);
		ft_putstr_fd("\n", 0);
	}
}

int		is_envvar_ending(char c)
{
	if (ft_isalnum(c))
		return (0);
	if (c == '_')
		return (0);
	return (1);
}

void	replace_env(t_command *cmd, int i, int j)
{
	int sizew;
	int w;
	char *new_word;

	j++;
	sizew = 0;
	while (!is_envvar_ending(cmd->words[i][j + sizew]) && cmd->words[i][j + sizew])
		sizew++;
	//printf("%d\n", sizew);
	w = 0;
	while (environ[w] && ft_strncmp(environ[w], cmd->words[i] + j, sizew))
		w++;
	j--;
	new_word = malloc(ft_strlen(cmd->words[i]) - (sizew + 1) + ft_strlen(environ[w]) - (sizew + 1) + 1);
	ft_memcpy(new_word, cmd->words[i], j);
	ft_memcpy(new_word + j, environ[w] + sizew + 1, ft_strlen(environ[w]) - (sizew + 1));
	//printf("%s\n", cmd->words[i] + sizew + 1);
	ft_strlcpy(new_word + j + ft_strlen(environ[w]) - (sizew + 1), cmd->words[i] + sizew + j + 1, ft_strlen(cmd->words[i]) - (sizew + 1) + 1);
	free(cmd->words[i]);
	cmd->words[i] = new_word;
}

void	lookfor_envvar(t_command *cmd)
{
	int i;
	int j;

	i = 0;
	while (cmd->words[i])
	{
		j = 0;
		while (cmd->words[i][j])
		{
			//printf("%c\n", cmd->words[i][j]);
			//printf("%d\n", cmd->quotes[i]);
			if (cmd->words[i][j] == '$' && !cmd->quotes[i])
			{
				//printf("%s\n", cmd->words[i]);
				// printf("%d\n", ft_strcmp(cmd->words[i + 1], "QUOTE"));
				replace_env(cmd, i, j);
				j--;
			}
			j++;
		}
		i++;
	}
}

int		stickem(t_command *cmd, int i)
{
	char *conc;
	int j;
	int conc_size;

	j = 1;
	conc_size = ft_strlen(cmd->words[i]) + ft_strlen(cmd->words[i + j]) + 1;
	conc = malloc(conc_size);
	ft_memcpy(conc, cmd->words[i], ft_strlen(cmd->words[i]));
	ft_strlcpy(conc + ft_strlen(cmd->words[i]), cmd->words[i + j], ft_strlen(cmd->words[i + j]) + 1);
	free(cmd->words[i]);
	cmd->words[i] = conc;
	while (cmd->words[i + j + 1])
	{
		free(cmd->words[i + j]);
		cmd->words[i + j] = ft_strdup(cmd->words[i + j + 1]);
		j++;
	}
	free(cmd->words[i + j]);
	free(cmd->words[i + j + 1]);
	cmd->words[i + j] = NULL;
	cmd->size--;
	return (1);
}

void	stick_words(t_command *cmd)
{
	int i;
	int offset;

	offset = 0;
	i = 0;
	while (cmd->stickits[i] != - 1)
	{
		if (cmd->stickits[i])
			offset += stickem(cmd, i - offset);
		i++;
	}
}

int		*execute_cmd(t_command *cmd)
{
	pid_t p_pid;
	int stt;
	char **path;
	char *bin;
	int *pipefd;

	pipefd = malloc(sizeof(int) * 2);
	path = get_path();
	lookfor_envvar(cmd);
	stick_words(cmd);
	//display_commands(&cmd);
	if (is_builtin(cmd->words[0]))
		return (exec_builtin(cmd));
	bin = get_bin(cmd->words[0], path);
	pipe(pipefd);
	p_pid = fork();
	if (p_pid == 0)
		fork_exec(bin, cmd, pipefd);
	else if (p_pid > 0)
		waitpid(p_pid, &stt, 0);
	clean_path(path);
	free(bin);
	if (!ft_strcmp(cmd->end_command, "PIPE"))
		return (pipefd);
	return (NULL);
}

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
		old_stdin = dup(1);
		ft_putstr_fd("miniwouf > ", 1);
		err = get_next_line(0, &line);
		get_lex(line, &lex);
		//display_lex(&lex);
		get_commands(lex, &commands);
		ft_lstclear(&lex, &free);
		//display_commands(&commands);
		deal_cmd(&commands);
		clean_commands(&commands);
		dup2(old_stdin, 0);
		dup2(old_stdout, 1);
	}

}