#include "../include/minishell.h"

void	print_my_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	print_env_list(t_env_list *list)
{
	while (list)
	{
		// printf("%s\n", list->key);
		// printf("%s\n", list->value);
		printf("%s\n", list->full);
		list = list->next;
	}
}

void	print_tokens(t_list *list)
{
	while(list)
	{
		printf("[%s]\n", (char *)list->content);
		list = list->next;
	}
}
