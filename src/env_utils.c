/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:35:23 by rjada             #+#    #+#             */
/*   Updated: 2022/05/27 13:37:16 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	env_del(t_env_list *env, void (*del)(void *))
{
	del(env->key);
	del(env->value);
	del(env->full);
	free(env);
}

void	env_clear(t_env_list **env, void (*del)(void *))
{
	if (env && *env)
	{
		env_clear(&(*env)->next, del);
		env_del(*env, del);
		*env = NULL;
	}
}

void	env_add_back(t_env_list **env, t_env_list *new)
{
	t_env_list	*tmp;

	if (!*env)
	{
		*env = new;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env_list	*env_new(char *str)
{
	char		*tmp;
	t_env_list	*ret;

	ret = malloc(sizeof(t_env_list));
	if (!ret)
		return (NULL);
	tmp = ft_strchr(str, '=');
	ret->key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(tmp));
	ret->value = ft_strdup(tmp + 1);
	ret->full = ft_strdup(str);
	ret->next = NULL;
	return (ret);
}
