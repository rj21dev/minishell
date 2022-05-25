#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

#define CLOSE "\001\033[0m\002"
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"

typedef struct s_env_list
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_info
{
	char				**envp;
	// char				**paths;
	// char				*infile;
	// char				*outfile;
	// int					cmd_num;
	// int					append;
	// char				*here_doc;
	t_env_list			*env;
	// t_simple_command	*simple_commands;
}	t_info;

void	push_spaces(char **line);
void	expand_quotes(t_env_list **env, char **line);
void	expand_dollar(t_env_list **env, char **line, int *i);
void	set_quote(char *quote, char c);

char	**set_envp(t_env_list *env);
char	*get_env(t_env_list **env, char *key);
t_env_list	*env_new(char *str);
t_env_list	*init_env(char **envp);
void		env_add_back(t_env_list **env, t_env_list *new);
void		env_clear(t_env_list **env, void (*del)(void *));

t_list	*lexer(t_env_list **env, char *line);

void	add_substr(char **str, int start, char *substr);
void	rm_substr(char **str, int start, int len);


#endif
