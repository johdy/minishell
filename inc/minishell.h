#ifndef MINISHELL_H
# define MINISHELL_H
# include "get_next_line.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <string.h>
# include <sys/errno.h>

typedef struct			s_command
{
	char				**words;
	int					size;
	void				*end_command;
	struct s_command	*next;
	int					*quotes;
	int					*stickits;
	int					old_stdin;
	int					old_stdout;
}						t_command;

void	clean_commands(t_command **cmds);
void	get_lex(char *line, t_list **lex);
void	deal_quotes(char *line, int *head_ptr, int *quotes, t_list **lex);
void	deal_cmp(char *line, int *head_ptr, t_list **lex);
void	deal_pipe_sc(char *line, int *head_ptr, t_list **lex);
void	add_back_normal_word(char* start, int size, t_list **lex);
void	clean_commands(t_command **cmds);
void	clean_path(char **path);
char	**get_path(char **ms_environ);
char	**ft_split_path(char *str, char c);
char	*get_bin(char *cmd, char **path);
int		*execute_cmd(t_command *cmd, char ***ms_environ, int old_stdin, int old_stdout);

//Get_commands
void	get_commands(t_list *lex, t_command **commands);
int		*get_stickits_nb(t_list *first, int size);
int		*get_quotes_nb(t_list *first, int size);
int		is_q_dq_st(char *tok, int quote, int dquote, int stickit);

//Redirections
int		how_to_open(char *redir, char *file);
void	deal_redirection(int *pipefd, t_command *cmd, int fd_open);

//Builtins
void	ft_echo(t_command *cmd);
void	ft_cd(t_command *cmd, char **ms_environ);
void	ft_pwd(t_command *cmd);
void	ft_exit(t_command *cmd, char **ms_environ, int *pipefd, char *bin);
void	ft_env(t_command *cmd, char **ms_environ);
void	ft_unset(t_command *cmd, char **ms_environ);
void	ft_export(t_command *cmd, char ***ms_environ);

//Correct
void	correct_cmd(t_command *cmd, char **ms_environ);
void	stick_words(t_command *cmd);
void	lookfor_envvar(t_command *cmd, char **ms_environ);

//Utils
int		is_end_command(char *token);
int		is_redirection_cmd(char *token);
void	display_commands(t_command **commands);
void	display_lex(t_list **lex);
int		ft_strcmp(char *s1, char *s2);
int		fetch_env(char *id, char **ms_environ, int size);
void	restore_std(int stdin, int stdout);
int		find_eq(char *str);

extern char **environ;
#endif