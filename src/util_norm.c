/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:30:12 by rjada             #+#    #+#             */
/*   Updated: 2022/05/30 19:15:40 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	cd_error(t_info *info, int i)
{
	ft_putstr_fd("cd: no such file or directory: ", STDERR);
	ft_putstr_fd(info->commands[i].argv[1], STDERR);
	ft_putstr_fd("\n", STDERR);
	g_exit = 1;
	return (1);
}

void	sig_handler(int sig)
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

void	free_commands(t_info **info)
{
	int	i;

	i = 0;
	if ((*info)->commands)
	{
		while (i < (*info)->cmd_num + 1)
		{
			if ((*info)->commands[i].argv)
				ft_split_free((*info)->commands[i].argv);
			i++;
		}
		if ((*info)->commands)
			free((*info)->commands);
	}
}

void	history(t_info **info)
{
	if (ft_strlen((*info)->line))
		add_history((*info)->line);
}

void	destructor(t_info **info)
{
	free((*info)->line);
	free_commands(info);
}
