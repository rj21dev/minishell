/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabradol <eabradol@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 16:38:05 by eabradol          #+#    #+#             */
/*   Updated: 2022/05/28 16:38:07 by eabradol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//вовзращает стрку с выделенйо памятью
char	*search_env_util(char *input)
{
	char	*str;
	int		i;

	i = -1;
	while (input[++i] && input[i] != '=')
		;
	str = malloc(sizeof(char ) * (i + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (input[i] && input[i] != '=')
	{
		str[i] = input[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	ex_env_addendum(t_env_list *env_ls, char *replec)
{
	int		i;
	char	*str;
	char	*str1;
	char	*input;

	i = -1;
	input = env_ls->full;
	while (input[++i] && input[i] != '=')
		;
	str = ft_substr(input, 0, i + 1);
	str1 = ft_substr(replec, i + 1, ft_strlen(replec) - i);
	input = ft_strjoin(str, str1);
	free_two_str(str, str1);
	free(env_ls->full);
	env_ls->full = input;
}

int	search_env_unil(t_info *inf, char *str)
{
	char		*str1;
	char		*str2;
	t_env_list	*tmp;

	tmp = inf->env;
	str1 = search_env_util(str);
	while (tmp->next)
	{
		str2 = search_env_util(tmp->full);
		if (str2 && str1 && !ft_strcmp(str1, str2))
		{
			ex_env_addendum(tmp, str);
			free(str2);
			free(str1);
			return (1);
		}
		free(str2);
		tmp = tmp->next;
	}
	free(str1);
	return (0);
}

int	search_env(t_info *inf, char *str)
{
	char		*str1;
	char		*str2;
	t_env_list	*tmp;
	int			flag;

	tmp = inf->env;
	flag = 0;
	str1 = search_env_util(str);
	flag = search_env_unil(inf, str);
	str2 = search_env_util(tmp->full);
	if (str2 && str1 && !ft_strcmp(str1, str2))
	{
		flag = 1;
		ex_env_addendum(tmp, str);
	}
	if (flag != 1)
	{
		free_two_str(str2, str1);
		return (1);
	}
	free_two_str(str2, str1);
	return (0);
}

int	export(t_info *info, int i)
{
	int	j;

	if (!info->commands[i].argv[1])
		printf_expot_env(info);
	else
	{
		j = 1;
		while (info->commands[i].argv[j])
		{
			if (ft_isalpha(info->commands[i].argv[j][0]))
			{
				if (1 == search_env(info, info->commands[i].argv[j]))
					set_env(info, info->commands[i].argv[j]);
			}
			else
			{
				ft_putendl_fd("export : not enough arguments", STDERR);
				g_exit = 1;
				return (1);
			}
			j++;
		}
		info->envp = set_envp(info->env);
	}
	return (1);
}
