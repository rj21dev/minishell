/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:35:04 by rjada             #+#    #+#             */
/*   Updated: 2022/05/30 18:56:24 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	run_bin(int num, t_info *info)
{
	char	**paths;
	int		i;

	paths = create_paths(info->commands[num].argv[0], info->envp);
	if (!paths)
		micro_print_err(info->commands[num].argv[0], 2);
	i = 0;
	while (paths[i])
	{
		if (!access(paths[i], X_OK))
			break ;
		i++;
		if (!paths[i])
			micro_print_err(info->commands[num].argv[0], 1);
	}
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	execve(paths[i], info->commands[num].argv, info->envp);
}

static int	check_cmd(char *cmd, int i, t_info *info)
{
	if (ft_strlen(cmd) == ft_strlen("echo") \
		&& !ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (echo(info, i));
	if (ft_strlen(cmd) == ft_strlen("cd") \
		&& !ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (ft_cd(info, i));
	if (ft_strlen(cmd) == ft_strlen("pwd") \
		&& !ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (pwd(info, i));
	if (ft_strlen(cmd) == ft_strlen("env") \
		&& !ft_strncmp(cmd, "env", ft_strlen("env")))
		return (env(info, i));
	if (ft_strlen(cmd) == ft_strlen("export") \
		&& !ft_strncmp(cmd, "export", ft_strlen("export")))
		return (export(info, i));
	if (ft_strlen(cmd) == ft_strlen("unset") \
		&& !ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (unset(info, i));
	if (ft_strlen(cmd) == ft_strlen("exit") \
		&& !ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (ft_exit(info, i));
	return (0);
}

static void	redirects(t_exec *exec, t_info *info, int i)
{
	dup2(exec->fdin, 0);
	close(exec->fdin);
	if (i == info->cmd_num)
		exec->fdout = get_out_file(exec->tmpout, info);
	else
	{
		pipe(exec->fdpipe);
		exec->fdout = exec->fdpipe[1];
		exec->fdin = exec->fdpipe[0];
	}
	dup2(exec->fdout, 1);
	close(exec->fdout);
}

int	check_status(t_exec exec)
{
	waitpid(exec.pid, &exec.tmpret, 0);
	if (WIFSIGNALED(exec.tmpret))
	{
		if (WTERMSIG(exec.tmpret) == SIGQUIT)
		{
			ft_putendl_fd("Quit: 3", STDOUT);
			return (131);
		}
		else if (WTERMSIG(exec.tmpret) == SIGINT)
		{
			ft_putendl_fd("", STDOUT);
			return (130);
		}
	}
	return (WEXITSTATUS(exec.tmpret));
}

void	executor(t_info *info)
{
	int			i;
	t_exec		exec;

	exec.fdin = save_fd_set_input(info, &exec);
	i = -1;
	while (info->cmd_num >= ++i)
	{
		redirects(&exec, info, i);
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		if (!check_cmd(info->commands->argv[0], i, info))
		{
			exec.pid = fork();
			if (exec.pid == 0)
				run_bin(i, info);
			g_exit = check_status(exec);
		}
	}
	restore_fd(&exec);
}
