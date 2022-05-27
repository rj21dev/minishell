/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:39:41 by rjada             #+#    #+#             */
/*   Updated: 2022/05/27 13:43:37 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
		ft_putendl_fd("", STDOUT);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
//добавить в exe_command
//char	*build_error_str(char *file)
//{
//    char	*error;
//    char	*tmp;
//
//    error = ft_strjoin("minishell", ": ");
//    tmp = error;
//    error = ft_strjoin(error, file);
//    free(tmp);
//    return (error);
//}
//
//void	micro_print_err(char *command)
//{
//    char	*err;
//
//    err = build_error_str(command);
//    write(2, err, ft_strlen(err));
//    write(2, ": ", 2);
//    write(2, "command not found", ft_strlen("command not found"));
//    write(2, "\n", 1);
//    if (err)
//        free(err);
//}
//
//void    ft_child(t_info *inf, char **command)
//{
//    char    **cmd_d;
//
//    cmd_d = re_build_command(command, inf);
//
//    execve(cmd_d[0], cmd_d, command);
//    micro_print_err(command[0]);
//    free_arr(command);
//    exit(127);
//}

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
    gl_exit = 0;
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
		if (!list)
			continue;
		// print_tokens(list);
		if (!validator(list))
		{
			ft_lstclear(&list, free);
			free(cmdline);
			continue;
		}
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
