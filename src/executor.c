/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:35:04 by rjada             #+#    #+#             */
/*   Updated: 2022/05/27 16:22:16 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_out_file(int tmpout, t_info *info)
{
	int	fdout;

	if (info->outfile)
	{
		if (info->append > 0)
			fdout = open(info->outfile, O_WRONLY | O_CREAT | O_APPEND,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
		else
			fdout = open(info->outfile, O_WRONLY | O_CREAT | O_TRUNC,
					S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP);
	}
	else
		fdout = dup(tmpout);
	return (fdout);
}

void	restore_fd(t_exec *exec)
{
	dup2(exec->tmpin, 0);
	dup2(exec->tmpout, 1);
	close(exec->tmpin);
	close(exec->tmpout);
	waitpid(exec->pid, &exec->tmpret, 0);
}

int	save_fd_set_input(t_info *info, t_exec *exec)
{
	int	fdin;

	exec->tmpin = dup(0);
	exec->tmpout = dup(1);
	if (info->infile)
		fdin = open(info->infile, O_RDONLY);
	else if (info->here_doc != 0)
		fdin = write_to_heredoc(info);
	else
		fdin = dup(exec->tmpin);
	return (fdin);
}

static char	**create_paths(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	**full_paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
		i++;
	full_paths = malloc(sizeof(char *) * (i + 2));
	cmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
		full_paths[i] = ft_strjoin(paths[i], cmd);
	full_paths[i] = cmd;
	full_paths[i + 1] = NULL;
	return (full_paths);
}

void	run_bin(int num, t_info *info)
{
	int			i;

	info->paths = create_paths(info->commands[num].argv[0], info->envp);
	i = 0;
	while (info->paths[i])
	{
		execve(info->paths[i], info->commands[num].argv, info->envp);
		i++;
	}
}

int	check_cmd(char *cmd, int i, t_info *info)
{
	if (!ft_strncmp(cmd, "echo", ft_strlen("echo")))
		return (echo(info, i));
	if (!ft_strncmp(cmd, "cd", ft_strlen("cd")))
		return (cd(info, i));
	if (!ft_strncmp(cmd, "pwd", ft_strlen("pwd")))
		return (pwd(info, i));
	if (!ft_strncmp(cmd, "env", ft_strlen("pwd")))
		return (env(info, i));
	if (!ft_strncmp(cmd, "export", ft_strlen("export")))
		return (export(info, i));
	if (!ft_strncmp(cmd, "unset", ft_strlen("unset")))
		return (unset(info, i));
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
		return (ft_exit(info, i));
	return (0);
}

void	executor(t_info *info)
{
	int			i;
	t_exec		exec;

	exec.fdin = save_fd_set_input(info, &exec);
	i = -1;
	while (info->cmd_num >= ++i)
	{
		dup2(exec.fdin, 0);
		close(exec.fdin);
		if (i == info->cmd_num)
			exec.fdout = get_out_file(exec.tmpout, info);
		else
		{
			pipe(exec.fdpipe);
			exec.fdout = exec.fdpipe[1];
			exec.fdin = exec.fdpipe[0];
		}
		dup2(exec.fdout, 1);
		close(exec.fdout);          
		if (!check_cmd(info->commands->argv[i], i, info))
		{
			exec.pid = fork();
			if (exec.pid == 0)
				run_bin(i, info);
		}
	}
	restore_fd(&exec);
}
