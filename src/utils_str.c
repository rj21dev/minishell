/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:40:15 by rjada             #+#    #+#             */
/*   Updated: 2022/05/27 13:40:17 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_substr(char **str, int start, char *substr)
{
	char	*new;
	char	*tmp;

	new = malloc(sizeof(char) * (ft_strlen(*str) + ft_strlen(substr) + 1));
	if (!new)
		return ;
	ft_strlcpy(new, *str, start + 1);
	ft_strlcpy(new + start, substr, start + ft_strlen(substr) + 1);
	ft_strlcpy(new + start + ft_strlen(substr), *str + start, \
			ft_strlen(*str) + ft_strlen(substr) + 1);
	tmp = *str;
	*str = new;
	free(tmp);
}

void	rm_substr(char **str, int start, int len)
{
	char	*new;
	char	*tmp;

	new = malloc(sizeof(char) * (ft_strlen(*str) - len + 1));
	if (!new)
		return ;
	ft_strlcpy(new, *str, start + 1);
	ft_strlcpy(new + start, *str + start + len, \
			ft_strlen(*str + start + len) + 1);
	tmp = *str;
	*str = new;
	free(tmp);
}
