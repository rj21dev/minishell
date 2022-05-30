/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eabradol <eabradol@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:30:12 by rjada             #+#    #+#             */
/*   Updated: 2022/05/30 14:17:44 by eabradol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*hocus_str(char *str1, char *str2)
{
	char	*str3;
	char	*str;

	str3 = ft_strjoin(str1, "=");
	str = ft_strjoin(str3, str2);
	free(str3);
	return (str);
}

void	rest_env(t_info *info, char *input, char *pwd)
{
	t_env_list	*tmp;
	char		*str3;

	tmp = info->env;
	while (tmp)
	{
		if (!ft_strcmp((tmp->key), input))
		{
			str3 = hocus_str(tmp->key, pwd);
			search_env(info, str3);
			free(str3);
			free(pwd);
		}
		tmp = tmp->next;
	}
}

char	*key_home(t_info *info, char *input)
{
	t_env_list	*tmp;

	tmp = info->env;
	while (tmp)
	{
		if (!ft_strcmp((tmp->key), input))
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (ft_strdup("/Users"));
}

int	cd_home(t_info *info)
{
	char	*pwd_now;
	char	*pwd_new;
	char	*home;

	pwd_now = malloc(1000);
	if (!pwd_now)
		return (0);
	pwd_now = getcwd(pwd_now, 1000);
	home = key_home(info, "HOME");
	chdir(home);
	rest_env(info, "OLDPWD", pwd_now);
	pwd_new = malloc(sizeof(char ) * 1000);
	if (!pwd_new)
		return (0);
	pwd_new = getcwd(pwd_new, 1000);
	rest_env(info, "PWD", pwd_new);
	free(home);
	return (1);
}

int	ft_cd(t_info *info, int i)
{
	char	*pwd_now;
	char	*pwd_new;

	if (!info->commands[i].argv[1])
		return (cd_home(info));
	if (0 > access(info->commands[i].argv[1], F_OK))
		return (cd_error(info, i));
	pwd_now = malloc(1000);
	if (!pwd_now)
		return (0);
	pwd_now = getcwd(pwd_now, 1000);
	rest_env(info, "OLDPWD", pwd_now);
	chdir(info->commands[i].argv[1]);
	pwd_new = malloc(sizeof(char ) * 1000);
	if (!pwd_new)
		return (0);
	pwd_new = getcwd(pwd_new, 1000);
	rest_env(info, "PWD", pwd_new);
	g_exit = 0;
	return (1);
}
