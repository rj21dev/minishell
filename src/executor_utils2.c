/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:03:17 by rjada             #+#    #+#             */
/*   Updated: 2022/05/29 16:03:19 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**upd_paths(char **paths, char *cmd, int i)
{
	char	**full_paths;
	char	*newcmd;
	char	*abs;
	char	*tmp;

	while (paths[i])
		i++;
	full_paths = malloc(sizeof(char *) * (i + 2));
	if (cmd[0] == '.')
	{
		tmp = ft_substr(cmd, 1, ft_strlen(cmd) - 1);
		abs = getcwd(NULL, 0);
		newcmd = ft_strjoin(abs, tmp);
		free(tmp);
		free(abs);
	}
	else
		newcmd = ft_strjoin("/", cmd);
	i = -1;
	while (paths[++i])
		full_paths[i] = ft_strjoin(paths[i], newcmd);
	full_paths[i] = ft_strdup(newcmd);
	full_paths[i + 1] = NULL;
	free(newcmd);
	return (full_paths);
}

char	**create_paths(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	**full_paths;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			paths = ft_split(envp[i] + 5, ':');
		i++;
	}
	if (!paths)
		return (NULL);
	full_paths = upd_paths(paths, cmd, 0);
	ft_split_free(paths);
	return (full_paths);
}
