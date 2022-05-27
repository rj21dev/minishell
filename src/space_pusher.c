/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_pusher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:40:11 by rjada             #+#    #+#             */
/*   Updated: 2022/05/27 13:40:13 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

static void	push_after(char **line)
{
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		set_quote(&quote, (*line)[i]);
		if (!quote && is_metachar((*line)[i]))
		{
			if ((*line)[i + 1] != (*line)[i] && (*line)[i + 1] != ' ')
				add_substr(line, ++i, " ");
			else if ((*line)[i + 1] == (*line)[i] \
					&& (*line)[i - 1] == (*line)[i])
				add_substr(line, ++i, " ");
		}
	}
}

static void	push_before(char **line)
{
	int		i;
	char	quote;

	quote = 0;
	i = -1;
	while ((*line)[++i])
	{
		set_quote(&quote, (*line)[i]);
		if ((!quote && i > 0 && (is_metachar((*line)[i]) \
				&& (*line)[i - 1] != (*line)[i] && (*line)[i - 1] != ' ')) \
				|| (quote != '\'' && (*line)[i] == '$' \
				&& (*line)[i - 1] != ' ' && (*line)[i - 1] != '"' \
				&& (*line)[i - 1] != '\'' && ft_isalpha((*line)[i + 1])))
			add_substr(line, i++, " ");
	}
}

void	push_spaces(char **line)
{
	push_before(line);
	push_after(line);
}
