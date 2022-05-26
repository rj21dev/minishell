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

void	init(t_info **info, char **envp)
{
	*info = (t_info *)malloc(sizeof(t_info));
	ft_memset(*info, 0, sizeof(t_info));
	(*info)->env = init_env(envp);
	(*info)->envp = set_envp((*info)->env);
	(*info)->infile = NULL;
	(*info)->outfile = NULL;
	(*info)->here_doc = NULL;
	(*info)->commands = NULL;
	(*info)->append = 0;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	free_commands(t_info **info)
{
	int	i;

	i = 0;
	if ((*info)->commands)
	{
		while ((*info)->commands[i].argv)
		{
			ft_split_free((*info)->commands[i].argv);
			i++;
		}
	}
}

void	re_init(t_info **info)
{
	if ((*info)->infile)
		free((*info)->infile);
	if ((*info)->outfile)
		free((*info)->outfile);
	if ((*info)->here_doc)
		free((*info)->here_doc);
	// if ((*info)->commands)
	// 	free_commands(info);
	(*info)->infile = NULL;
	(*info)->outfile = NULL;
	(*info)->here_doc = NULL;
	(*info)->append = 0;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	char	*cmdline;
	t_info	*info;
	t_list	*list;

	if (argc != 1)
		return (1);

	init(&info, envp);
	while(1)
	{
		re_init(&info);
		cmdline = readline("ebash $ ");
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
		// print_tokens(list);
		parser(&list, info);
		ft_lstclear(&list, free);
		// printf("%d\n", info->append);
		// printf("%s\n", cmdline);
		// print_my_envp(info->envp);
		// print_env_list(info->env);
		// printf("%s\n", info->infile);
		// printf("%s\n", info->outfile);
		// printf("%s %s\n", info->commands[0].argv[0], info->commands[0].argv[1]);
		// printf("%s %s\n", info->commands[1].argv[0], info->commands[1].argv[1]);

		// TODO token validator
		executor(info);
		free(cmdline);
	}
	rl_clear_history();
	ft_split_free(info->envp);
	env_clear(&info->env, free);
	free(info);
	ft_putendl_fd("exit", STDOUT);
	// exit(0);
}
