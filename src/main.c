/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:39:41 by rjada             #+#    #+#             */
/*   Updated: 2022/05/28 13:42:30 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_handler(int sig)
{
	rl_on_new_line();
	rl_redisplay();
	if (sig == SIGINT)
	{
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
//добавить
void    minishell_patch(void)
{
    char    *str;
    char    *str3;
    char    *str1;

    str = malloc(sizeof(char) * 1000);
    if (!str)
        return ;
    str = getcwd(str, 1000);
    if (str) {
        str1 = ft_strjoin(str, "/./minishell");
        free(str);
        str3 = ft_strjoin("_=", str1);
        free(str1);
//        search_env(inf, str3);
        free(str3);
    }
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
//    minishell_patch();
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
    g_exit = 0;
	init(&info, envp);
	while(1)
	{
		re_init(&info);
		cmdline = readline("minishell $ ");
		if (!cmdline)
			break;
		add_history(cmdline);
		if (find_not_pair_quote(cmdline))
		{
			ft_putendl_fd("minishell: unmatched quotes", STDERR);
			free(cmdline);
			continue;
		}
		push_spaces(&cmdline);
		list = lexer(&info->env, cmdline);
		if (!list)
			continue;
		if (!validator(list))
		{
			ft_lstclear(&list, free);
			free(cmdline);
			continue;
		}
		parser(&list, info);
		ft_lstclear(&list, free);
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
