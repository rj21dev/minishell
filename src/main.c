#include "../include/minishell.h"
#include "../include/debug_print.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("", STDOUT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	find_not_pair_quote(const char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (!*str)
				return (1);
		}
		if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (!*str)
				return (1);
		}
		str++;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)envp;
	char	*cmdline;
	t_info	*info;
	t_list	*list;

	if (argc != 1)
		return (1);

	info = (t_info *)malloc(sizeof(t_info));
	ft_memset(info, 0, sizeof(info));
	info->env = init_env(envp);
	info->envp = set_envp(info->env);

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		cmdline = readline(BEGIN(49, 34)"fuckingshell $ "CLOSE);
		if (!cmdline)
			break;
		add_history(cmdline);
		if (find_not_pair_quote(cmdline))
		{
			ft_putendl_fd("Error: unmatched quotes", STDERR);
			free(cmdline);
			continue;
		}
		push_spaces(&cmdline);
		list = lexer(&info->env, cmdline);
		print_tokens(list);
		ft_lstclear(&list, free);
		// printf("%s\n", cmdline);
		// print_my_envp(info->envp);
		// print_env_list(info->env);
		free(cmdline);
	}
	rl_clear_history();
	ft_split_free(info->envp);
	env_clear(&info->env, free);
	free(info);
	ft_putendl_fd("exit", STDOUT);
	// exit(0);
}
