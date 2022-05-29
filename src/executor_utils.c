/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 13:45:38 by rjada             #+#    #+#             */
/*   Updated: 2022/05/29 16:00:09 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*build_error_str(char *file)
{
	char	*error;
	char	*tmp;

	error = ft_strjoin("minishell", ": ");
	tmp = error;
	error = ft_strjoin(error, file);
	free(tmp);
	return (error);
}

void	micro_print_err(char *command, int i)
{
	char	*err;

	err = build_error_str(command);
	write(2, err, ft_strlen(err));
	write(2, ": ", 2);
	if (i == 1)
		write(2, "command not found", ft_strlen("command not found"));
	if (i == 2)
		write(2, "No such file or directory", \
		ft_strlen("No such file or directory"));
	write(2, "\n", 1);
	if (err)
		free(err);
	exit(127);
}

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
