#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;

	if (argc != 1)
		return (1);

	ft_putendl_fd("fuckingshell is under cunstruction!", STDOUT);
	return (0);
}
