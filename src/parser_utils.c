/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:40:01 by rjada             #+#    #+#             */
/*   Updated: 2022/05/27 13:40:03 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	lst_cnt(char *str, t_list *token_lst)
{
	int	count;

	count = 0;
	while (token_lst)
	{
		if (ft_strncmp(token_lst->content, str, ft_strlen(str)) == 0
			&& ft_strlen(token_lst->content) == ft_strlen(str))
			count++;
		token_lst = token_lst->next;
	}
	return (count);
}

int	count_cmd(t_list *token_lst)
{
	t_list	*temp;
	int		count;

	count = 0;
	temp = token_lst;
	while (temp && temp->content)
	{
		if (ft_strlen(temp->content) == 2
			&& ft_strncmp(temp->content, "<<", ft_strlen(temp->content)) == 0)
			count -= 2;
		if (ft_strlen(temp->content) == 1
			&& (ft_strncmp(temp->content, "|", ft_strlen(temp->content)) == 0 \
			|| ft_strncmp(temp->content, ">", ft_strlen(temp->content)) == 0))
			return (count);
		if (ft_strlen(temp->content) == 2
			&& ft_strncmp(temp->content, ">>", 2) == 0)
			return (count);
		count++;
		temp = temp->next;
	}
	return (count);
}

t_cmd	*pipe_cut(t_list *toks, t_cmd *pipes, t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (toks && ft_strncmp(toks->content, ">", 1) != 0)
	{
		if (ft_strncmp(toks->content, "|", ft_strlen(toks->content)) == 0)
		{
			i++;
			pipes[i].argv = malloc(sizeof(char *)
					* (count_cmd(toks->next) + 1));
			j = 0;
			toks = toks->next;
		}
		pipes[i].argv[j] = ft_strdup(toks->content);
		pipes[i].argc = ++j;
		pipes[i].argv[j] = NULL;
		toks = toks->next;
	}
	info->cmd_num = i;
	return (pipes);
}
