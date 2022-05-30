/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:41:01 by rjada             #+#    #+#             */
/*   Updated: 2022/05/30 19:18:04 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>

extern void	rl_replace_line(const char *arg1, int arg2);
extern void	rl_clear_history(void);

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
	char				*line;
	char				*infile;
	char				*outfile;
	int					cmd_num;
	int					append;
	char				*here_doc;
	t_list				*tk_list;
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

int	g_exit;

char		**set_envp(t_env_list *env);
char		*get_env(t_env_list *env, char *key);
t_env_list	*env_new(char *str);
t_env_list	*init_env(char **envp);
void		env_add_back(t_env_list **env, t_env_list *new);
void		env_clear(t_env_list **env, void (*del)(void *));
void		set_env(t_info *info, char *str);
void		unset_env(t_info *info, char *key);
void		env_del(t_env_list *env, void (*del)(void *));

void		push_spaces(char **line);
void		expand_quotes(t_env_list *env, char **line);
void		expand_dollar(t_env_list *env, char **line, int *i);
void		set_quote(char *quote, char c);
int			find_not_pair_quote(const char *str);
t_list		*lexer(t_env_list *env, char *line);
void		parser(t_list **token_lst, t_info *info);
int			validator(t_list *token_lst);
int			lst_cnt(char *str, t_list *token_lst);
int			count_cmd(t_list *token_lst);
t_cmd		*pipe_cut(t_list *toks, t_cmd *pipes, t_info *info);

void		add_substr(char **str, int start, char *substr);
void		rm_substr(char **str, int start, int len);

int			write_to_heredoc(t_info *info);
void		micro_print_err(char *command, int i);
int			get_out_file(int tmpout, t_info *info);
int			save_fd_set_input(t_info *info, t_exec *exec);
void		restore_fd(t_exec *exec);
char		**create_paths(char *cmd, char **envp);
void		executor(t_info *info);

int			echo(t_info *info, int i);
int			ft_cd(t_info *info, int i);
int			pwd(t_info *info, int i);
int			export(t_info *info, int i);
int			unset(t_info *info, int i);
int			ft_exit(t_info *info, int i);
int			env(t_info *info, int i);

void		sig_handler(int sig);
int			cd_error(t_info *info, int i);
int			export_norm(t_info *info, int i);
char		*search_env_util(char *input);
void		shell_level(t_info *inf);
int			search_env(t_info *inf, char *str);
void		printf_expot_env(t_info *info);
void		free_two_str(char *s1, char *s2);
int			ft_strcmp(const char *s1, const char *s2);
void		free_commands(t_info **info);
void		destructor(t_info **info);
void		history(t_info **info);

#endif
