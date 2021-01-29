#include "minishell.h"

void	wait_for_it(int *stt, pid_t p_pid)
{
	signal(SIGINT, sigc_fork);
	signal(SIGQUIT, sigbs_fork);
	waitpid(p_pid, stt, 0);
}
