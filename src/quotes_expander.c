/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_expander.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:40:08 by rjada             #+#    #+#             */
/*   Updated: 2022/05/28 21:55:30 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	get_first_quote(char *line)
{
	char	ret;
	char	*dbl;
	char	*single;

	ret = 0;
	dbl = ft_strchr(line, '\"');
	single = ft_strchr(line, '\'');
	if (!dbl && single)
		ret = '\'';
	else if (dbl && !single)
		ret = '\"';
	else if (dbl && single)
	{
		if (ft_strlen(dbl) > ft_strlen(single))
			ret = '\"';
		else
			ret = '\'';
	}
	return (ret);
}

void	expand_quotes(t_env_list *env, char **line)
{
	int		i;
	int		should_get_quote;
	char	quote;

	should_get_quote = 0;
	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		if (!should_get_quote)
			quote = get_first_quote(&((*line)[i]));
		if (quote != '\'' && (((*line)[i] == '$') || \
			((*line)[i] == '$' && (*line)[i + 1] == '?')))
			expand_dollar(env, line, &i);
		if (quote && (*line)[i] == quote)
		{
			rm_substr(line, i--, 1);
			should_get_quote ^= 1;
		}
	}
}

void	set_quote(char *quote, char c)
{
	if (!*quote && (c == '\'' || c == '"'))
		*quote = c;
	else if (*quote == c)
		*quote = 0;
}

int	find_not_pair_quote(const char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str && *str != '\'')
				str++;
			if (!*str)
				return (1);
		}
		if (*str == '\"')
		{
			str++;
			while (*str && *str != '\"')
				str++;
			if (!*str)
				return (1);
		}
		str++;
	}
	return (0);
}
