#ifndef DEBUG_PRINT
# define DEBUG_PRINT

# include "minishell.h"

void	print_my_envp(char **envp);
void	print_env_list(t_env_list *list);
void	print_tokens(t_list *list);

#endif