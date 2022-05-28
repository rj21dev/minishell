/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:39:20 by rjada             #+#    #+#             */
/*   Updated: 2022/05/28 21:59:04 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_env(t_info *info, char *str)
{
	int		i;
	char	**tmp;

	env_add_back(&info->env, env_new(str));
	tmp = info->envp;
	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
	info->envp = set_envp(info->env);
}

void	unset_env(t_info *info, char *key)
{
	int			i;
	char		**tmp_envp;
	t_env_list	*prev;
	t_env_list	*tmp_env;

	tmp_env = info->env;
	while (tmp_env)
	{
		if (ft_strlen(key) == ft_strlen(tmp_env->key) \
				&& !ft_strncmp(key, tmp_env->key, ft_strlen(key)))
		{
			env_del(tmp_env, free);
			prev->next = tmp_env->next;
		}
		prev = tmp_env;
		tmp_env = tmp_env->next;
	}
	tmp_envp = info->envp;
	i = 0;
	while (tmp_envp[i])
		free(tmp_envp[i++]);
	free(tmp_envp);
	info->envp = set_envp(info->env);
}

char	*get_env(t_env_list *env, char *key)
{
	t_env_list	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strlen(key) == ft_strlen(tmp->key) \
				&& !ft_strncmp(key, tmp->key, ft_strlen(key)))
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

char	**set_envp(t_env_list *env)
{
	int			i;
	int			len;
	char		**ret;
	t_env_list	*tmp;

	len = 1;
	tmp = env;
	while (tmp->next && ++len)
		tmp = tmp->next;
	ret = malloc(sizeof(char *) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	tmp = env;
	while (tmp)
	{
		ret[i++] = ft_strdup(tmp->full);
		tmp = tmp->next;
	}
	ret[i] = NULL;
	return (ret);
}

t_env_list	*init_env(char **envp)
{
	int			i;
	t_env_list	*env;

	env = NULL;
	i = 0;
	while (envp[i])
		env_add_back(&env, env_new(envp[i++]));
	return (env);
}
