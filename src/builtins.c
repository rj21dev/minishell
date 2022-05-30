/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabradol <eabradol@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:12:45 by rjada             #+#    #+#             */
/*   Updated: 2022/05/30 18:53:50 by eabradol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	echo(t_info *info, int i)
{
	int			j;
	int			should_nl;
	const char	*tmp = info->commands[i].argv[1];

	j = 1;
	should_nl = 1;
	if (ft_strlen(tmp) == ft_strlen("-n") \
		&& !ft_strncmp(tmp, "-n", ft_strlen("-n")) && ++j)
		should_nl = 0;
	while (info->commands[i].argv[j])
	{
		ft_putstr_fd(info->commands[i].argv[j++], 1);
		if (info->commands[i].argv[j])
			ft_putchar_fd(' ', 1);
	}
	if (should_nl)
		ft_putchar_fd('\n', 1);
	g_exit = 0;
	return (1);
}

int	pwd(t_info *info, int i)
{
	char	*path;

	(void)info;
	(void)i;
	path = getcwd(NULL, 0);
	ft_putendl_fd(path, STDOUT);
	free(path);
	g_exit = 0;
	return (1);
}

int	unset(t_info *info, int i)
{
	int	j;

	j = 1;
	if (ft_strchr(info->commands[i].argv[1], '='))
	{
		ft_putstr_fd("unset: `", STDERR);
		ft_putstr_fd(info->commands[i].argv[1], STDERR);
		ft_putendl_fd("': not a valid identifier", STDERR);
		g_exit = 1;
		return (1);
	}
	while (info->commands[i].argv[j])
	{
		unset_env(info, info->commands[i].argv[j]);
		j++;
	}
	g_exit = 0;
	return (1);
}

int	env(t_info *info, int i)
{
	t_env_list	*tmp;

	if (info->commands[i].argv[1])
	{
		ft_putendl_fd("env: too many arguments", STDERR);
		g_exit = 1;
		return (1);
	}
	tmp = info->env;
	while (tmp)
	{
		ft_putendl_fd(tmp->full, STDOUT);
		tmp = tmp->next;
	}
	g_exit = 0;
	return (1);
}
