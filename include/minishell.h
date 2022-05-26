#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

extern void rl_replace_line(const char *, int);
extern void rl_clear_history(void);

typedef struct s_env_list
{
	char				*key;
	char				*value;
	char				*full;
	struct s_env_list	*next;
}	t_env_list;

typedef struct s_cmd
{
	int		argc;
	char	**argv;
}	t_cmd;

typedef struct s_info
{
	char				**envp;
	char				**paths;
	char				*infile;
	char				*outfile;
	int					cmd_num;
	int					append;
	char				*here_doc;
	t_env_list			*env;
	t_cmd				*commands;
}	t_info;

typedef struct s_exec
{
	int		tmpin;
	int		tmpout;
	int		fdpipe[2];
	int		tmpret;
	int		fdin;
	int		fdout;
	pid_t	pid;

}	t_exec;

void	push_spaces(char **line);
void	expand_quotes(t_env_list **env, char **line);
void	expand_dollar(t_env_list **env, char **line, int *i);
void	set_quote(char *quote, char c);
int		find_not_pair_quote(const char *str);

char		**set_envp(t_env_list *env);
char		*get_env(t_env_list **env, char *key);
t_env_list	*env_new(char *str);
t_env_list	*init_env(char **envp);
void		env_add_back(t_env_list **env, t_env_list *new);
void		env_clear(t_env_list **env, void (*del)(void *));

t_list	*lexer(t_env_list **env, char *line);
void	parser(t_list **token_lst, t_info *info);
int		validator(t_list *token_lst);
int		lst_cnt(char *str, t_list *token_lst);
int		count_cmd(t_list *token_lst);
t_cmd	*pipe_cut(t_list *toks, t_cmd *pipes, t_info *info);

void	add_substr(char **str, int start, char *substr);
void	rm_substr(char **str, int start, int len);

int		write_to_heredoc(t_info *info);
void	executor(t_info *info);

#endif
