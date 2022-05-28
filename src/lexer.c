/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:39:32 by rjada             #+#    #+#             */
/*   Updated: 2022/05/28 21:56:37 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	toklen(char *line)
{
	int		ret;
	char	quote;

	ret = 0;
	quote = 0;
	while (*line)
	{
		if (*line != ' ')
		{
			if (!quote)
				++ret;
			while (*line && *line != ' ')
				set_quote(&quote, *line++);
		}
		else
			++line;
	}
	return (ret);
}

static int	tokeniser(char ***tokens, char *line)
{
	int		i;
	int		len;
	char	quote;

	*tokens = malloc(sizeof(char *) * (toklen(line) + 1));
	if (!(*tokens))
		return (0);
	i = 0;
	quote = 0;
	while (*line)
	{
		if (*line != ' ')
		{
			if (!quote)
				len = 0;
			while (*line && *line != ' ' && ++len)
				set_quote(&quote, *line++);
			if (!quote)
				(*tokens)[i++] = ft_substr(line - len, 0, len);
		}
		else if (++line && quote)
			++len;
	}
	(*tokens)[i] = 0;
	return (i);
}

t_list	*lexer(t_env_list *env, char *line)
{
	int		len;
	char	**tokens;
	t_list	*ret;

	len = tokeniser(&tokens, line);
	ret = 0;
	while (len--)
	{
		expand_quotes(env, &tokens[len]);
		if (ft_strlen(tokens[len]))
			ft_lstadd_front(&ret, ft_lstnew(tokens[len]));
	}
	free(tokens);
	if (!validator(ret))
	{
		ft_lstclear(&ret, free);
		ret = NULL;
	}
	return (ret);
}
