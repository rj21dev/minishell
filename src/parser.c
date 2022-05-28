/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:40:05 by rjada             #+#    #+#             */
/*   Updated: 2022/05/28 17:19:25 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	skip_here_doc(t_list **token_lst, t_info *info)
{
	t_list	*ret;

	ret = *token_lst;
	if (ft_lstsize(*token_lst) < 3)
		return ;
	if (ft_strncmp("<<", (*token_lst)->content,
			ft_strlen((*token_lst)->content)) == 0
		&& (ft_strlen((*token_lst)->content) == ft_strlen("<<")))
	{
		ret = (*token_lst)->next->next;
		info->here_doc = ft_strdup((*token_lst)->next->content);
		free((*token_lst)->next);
		free(*token_lst);
		*token_lst = ret;
	}
	else if (ft_strncmp("<<", (*token_lst)->next->content,
			ft_strlen((*token_lst)->next->content)) == 0
		&& (ft_strlen((*token_lst)->next->content) == ft_strlen("<<")))
	{
		info->here_doc = ft_strdup((*token_lst)->next->next->content);
		ret = (*token_lst)->next->next->next;
		ft_lstdelone((*token_lst)->next->next, free);
		ft_lstdelone((*token_lst)->next, free);
		(*token_lst)->next = ret;
	}
}

static t_cmd	*find_pipes(t_list **token_lst, t_info *info)
{
	t_cmd	*pipes;
	t_list	*temp;

	temp = *token_lst;
	if (ft_strncmp(temp->content, "<", 1) == 0)
		temp = temp->next->next;
	pipes = malloc(sizeof(t_cmd) * (lst_cnt("|", temp) + 2));
	pipes[0].argv = malloc(sizeof(char *) * (count_cmd(temp) + 1));
	pipes = pipe_cut(temp, pipes, info);
	return (pipes);
}

static void	find_out_file(t_list *token_lst, t_info *info)
{
	t_list	*temp;

	temp = token_lst;
	info->append = 0;
	while (temp)
	{
		if (ft_strncmp(temp->content, ">", ft_strlen(temp->content)) == 0)
			info->outfile = ft_strdup(temp->next->content);
		else if (ft_strncmp(temp->content, ">>", ft_strlen(temp->content)) == 0)
		{
			info->outfile = ft_strdup(temp->next->content);
			info->append = 1;
		}
		temp = temp->next;
	}
}

static void	find_in_file(t_list *token_lst, t_info *info)
{
	t_list	*temp;

	temp = token_lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, "<<", ft_strlen(temp->content)) == 0
			&& ft_strlen(temp->content) == ft_strlen("<<"))
			return ;
		if (ft_strncmp(temp->content, "<", ft_strlen(temp->content)) == 0
			&& ft_strlen(temp->content) == ft_strlen("<"))
			info->infile = ft_strdup(temp->next->content);
		temp = temp->next;
	}
}

void	parser(t_list **token_lst, t_info *info)
{
	if (!*token_lst)
		return ;
	find_out_file(*token_lst, info);
	find_in_file(*token_lst, info);
	skip_here_doc(token_lst, info);
	info->commands = find_pipes(token_lst, info);
}
