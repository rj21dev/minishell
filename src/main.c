#include "../include/minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("", STDOUT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;

	if (argc != 1)
		return (1);

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		char *str = readline(BEGIN(49, 34)"fuckingshell $ "CLOSE);
		if (!str)
			break;
		add_history(str);
		free(str);
	}
	ft_putendl_fd("exit", STDOUT);
	return (0);
}
