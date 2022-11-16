
#include "minishell.h"

static void handler(int signum)
{
	if (signum == SIGINT)
		printf("\n");
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void    set_signal(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, handler);
}

static void	execute_handler(int signum)
{
	if (signum == SIGINT)
		exit(0);
}

void	set_execute_signal(void)
{
	signal(SIGINT, execute_handler);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, execute_handler);
}
