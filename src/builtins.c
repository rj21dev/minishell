#include "../include/minishell.h"

int echo(t_info *info, int i)
{
    int			j;
	int			should_nl;
	const char	*tmp = info->commands[i].argv[1];

	j = 1;
	should_nl = 1;
	if (ft_strlen(tmp) == ft_strlen("-n") \
		&& !ft_strncmp(tmp, "-n", ft_strlen("-n")) && ++j)
		should_nl = 0;
	while (info->commands[i].argv[j])
	{
		ft_putstr_fd(info->commands[i].argv[j++], 1);
		if (info->commands[i].argv[j])
			ft_putchar_fd(' ', 1);
	}
	if (should_nl)
		ft_putchar_fd('\n', 1);
    return (1);
}

int cd(t_info *info, int i)
{
    (void)i;
    (void)info;
    printf("This is cd\n");
    return (1);
}

int pwd(t_info *info, int i)
{
    if (info->commands[i].argv[1])
    {
        ft_putendl_fd("pwd: too many arguments", STDERR);
        //global_exit = 1;
        return (1);
    }
    printf("This is pwd\n");
    return (1);
}

int export(t_info *info, int i)
{
    (void)i;
    (void)info;
    printf("This is export\n");
    return (1);
}

int unset(t_info *info, int i)
{
    (void)i;
    (void)info;
    printf("This is unset\n");
    return (1);
}

int ft_exit(t_info *info, int i)
{
    if (info->commands[i].argv[1])
        exit(ft_atoi(info->commands[i].argv[1]));
    else
        exit(0); //TODO global_exit
    return (1);
}

int env(t_info *info, int i)
{
    t_env_list  *tmp;

    if (info->commands[i].argv[1])
    {
        ft_putendl_fd("env: too many arguments", STDERR);
        //global_exit = 1;
        return (1);
    }
    tmp = info->env;
	while (tmp)
	{
        ft_putendl_fd(tmp->full, STDOUT);
		tmp = tmp->next;
	}
    return (1);
}
