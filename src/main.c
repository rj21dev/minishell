/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:39:41 by rjada             #+#    #+#             */
/*   Updated: 2022/05/29 14:19:50 by rjada            ###   ########.fr       */
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
void    minishell_patch(t_info *info)
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
        search_env(info, str3);
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
    minishell_patch(*info);
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
		free((*info)->commands);
	}
}

void	re_init(t_info **info)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	if ((*info)->infile)
		free((*info)->infile);
	if ((*info)->outfile)
		free((*info)->outfile);
	if ((*info)->here_doc)
		free((*info)->here_doc);
	(*info)->infile = NULL;
	(*info)->outfile = NULL;
	(*info)->here_doc = NULL;
	(*info)->append = 0;
}

void	shell_loop(t_info **info)
{
	while(1)
	{
		re_init(info);
		(*info)->line = readline("minishell $ ");
		if (!(*info)->line)
			break;
		add_history((*info)->line);
		if (find_not_pair_quote((*info)->line))
		{
			ft_putendl_fd("minishell: unmatched quotes", STDERR);
			free((*info)->line);
			continue;
		}
		push_spaces(&((*info)->line));
		(*info)->tk_list = lexer((*info)->env, (*info)->line);
		if (!(*info)->tk_list)
		{
			free((*info)->line);
			continue;
		}
		parser(&((*info)->tk_list), *info);
		ft_lstclear(&((*info)->tk_list), free);
		executor(*info);
		free((*info)->line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	t_info	*info;

	if (argc != 1)
		return (1);
    g_exit = 0;
	init(&info, envp);
    shell_level(info);
	shell_loop(&info);
	rl_clear_history();
	ft_split_free(info->envp);
	env_clear(&info->env, free);
	free_commands(&info);
	free(info);
	ft_putendl_fd("exit", STDOUT);
	exit(0);
}
