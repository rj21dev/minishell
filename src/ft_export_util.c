/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_util.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabradol <eabradol@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:38:08 by eabradol          #+#    #+#             */
/*   Updated: 2022/05/30 14:19:48 by eabradol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

void	free_two_str(char *s1, char *s2)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
}

void	printf_expot_env(t_info *info)
{
	t_env_list	*tmp;

	tmp = info->env;
	while (tmp->next)
	{
		ft_putstr_fd("declare -x ", STDERR);
		ft_putstr_fd(tmp->full, STDERR);
		ft_putstr_fd("\n", STDERR);
		tmp = tmp->next;
	}
	ft_putstr_fd("declare -x ", STDERR);
	ft_putstr_fd(tmp->key, STDERR);
	ft_putstr_fd("\n", STDERR);
}

int	export(t_info *info, int i)
{
	if (!info->commands[i].argv[1])
		printf_expot_env(info);
	else
	{
		export_norm(info, i);
		ft_split_free(info->envp);
		info->envp = set_envp(info->env);
	}
	g_exit = 0;
	return (1);
}
