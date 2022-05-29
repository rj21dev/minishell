#include "../include/minishell.h"

char    *hocus_str(char *str1, char *str2)
{
    char *str3;
    char *str;

    str3 = ft_strjoin(str1, "=");
    str = ft_strjoin(str3, str2);
    free(str3);
    printf("hocus_str:%s\n", str);
    return (str);
}

void    rest_env(t_info *info, char *input, char *pwd)
{
    t_env_list  *tmp;

    tmp = info->env;
    while (tmp)
    {
        if (!ft_strcmp((tmp->key), input)) {
            search_env(info, pwd);
            free(pwd);
        }
        tmp = tmp->next;
    }
}

char    *key_home(t_info *info, char *input)
{
    t_env_list  *tmp;

    tmp = info->env;
    while (tmp)
    {
        if (!ft_strcmp((tmp->key), input)) {
            return (ft_strdup(tmp->value));
        }
        tmp = tmp->next;
    }
    return (ft_strdup("/Users"));
}

int	ft_cd(t_info *info, int i)
{
    char        *pwd_now;
    char        *pwd_new;
    char        *home;

    pwd_now = malloc(1000);
    if (!pwd_now)
        return (0);
    pwd_now = getcwd(pwd_now, 1000);
    if (!info->commands[i].argv[1]) {
        home = key_home(info, "HOME");
        chdir(home);
        rest_env(info, "OLDPWD", pwd_now);
        pwd_new = malloc(sizeof(char ) * 1000);
        if (!pwd_new)
            return (0);
        pwd_new = getcwd(pwd_new, 1000);
        rest_env(info, "PWD", pwd_new);
        free(home);
        return (1);
    }
    if (0 > access(info->commands[i].argv[1], F_OK))
    {
        ft_putstr_fd("cd: no such file or directory: ", STDERR);
        ft_putstr_fd(info->commands[i].argv[1], STDERR);
        ft_putstr_fd("\n", STDERR);
        free(pwd_now);
        g_exit = 1;
        return (1);
    }
    rest_env(info, "OLDPWD", pwd_now);
    chdir(info->commands[i].argv[1]);
    pwd_now = malloc(sizeof(char ) * 1000);
    if (!pwd_now) {
        pwd_now = malloc(1000);
        if (!pwd_now)
            return (0);
    }
    rest_env(info, "PWD", pwd_now);
    g_exit = 0;
    return (1);
}
