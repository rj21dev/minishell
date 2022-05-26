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
	full_paths[i + 1] = 0;
	return (full_paths);
}

int	run_bin(int num, t_info *info)
{
	int			i;

	info->paths = create_paths(info->commands[num].argv[0], info->envp);
	i = -1;
	while (info->paths[++i])
	{
		execve(info->paths[i], info->commands[num].argv, info->envp);
	}
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
		exec.pid = fork();
		if (exec.pid == 0)
			run_bin(i, info);
	}
	restore_fd(&exec);
}
