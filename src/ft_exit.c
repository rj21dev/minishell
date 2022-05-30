/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabradol <eabradol@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:18:46 by rjada             #+#    #+#             */
/*   Updated: 2022/05/30 14:11:46 by eabradol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

int	len_argvs(char **ar)
{
	int	str;

	str = 0;
	while (ar[str])
		str++;
	return (str);
}

int	is_numbers_to_string(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}

static void	ft_exit_util(char **code)
{
	if (is_numbers_to_string(code[1]))
	{
		ft_putstr_fd("exit\n", 1);
		exit(ft_atoi(code[1]));
	}
	else
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: ", 1);
		ft_putstr_fd(code[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
}

int	ft_exit(t_info *info, int i)
{
	char	**code;

	code = info->commands[i].argv;
	if (!code || !*code)
		exit(0);
	if (len_argvs(code) == 1)
	{
		ft_putstr_fd("exit\n", 1);
		exit(0);
	}
	else if (len_argvs(code) == 2)
		ft_exit_util(code);
	else
	{
		ft_putstr_fd("exit\n", 1);
		ft_putstr_fd("minishell: exit: too many arguments\n", 1);
		g_exit = 1;
		return (1);
	}
	return (1);
}
