/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:35:15 by rjada             #+#    #+#             */
/*   Updated: 2022/05/28 21:55:54 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*get_key(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i])
		if (str[i] == ' ' || str[i] == '"' || str[i] == '\'')
			break ;
	ret = ft_substr(str, 0, i);
	return (ret);
}

//добавить
void	expand_dollar(t_env_list *env, char **line, int *i)
{
	int		len;
	char	*key;
	char	*value;

	key = get_key(&(*line)[*i + 1]);
	if (!ft_strncmp(key, "?", 1))
		value = ft_itoa(g_exit);
	else if (ft_strlen(*line) == 1 || !ft_strncmp(*line, "$\"", 2) \
				|| !ft_strncmp(*line, "$ ", 2))
		value = "$";
	else
		value = get_env(env, key);
	len = ft_strlen(key);
	rm_substr(line, *i, len + 1);
	free(key);
	add_substr(line, *i, value);
	*i += ft_strlen(value) - 1;
}
