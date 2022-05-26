#include "../include/minishell.h"

static char	*get_key(char *str)
{
	int		i;
	char	*ret;

	i = -1;
	while (str[++i])
		if (str[i] == ' ' || str[i] == '"' || str[i] == '\'')
			break ;
	ret = ft_substr(str, 0, i);
	return (ret);
}

void	expand_dollar(t_env_list **env, char **line, int *i)
{
	int		len;
	char	*key;
	char	*value;

	key = get_key(&(*line)[*i + 1]);
	value = get_env(env, key);
	len = ft_strlen(key);
	rm_substr(line, *i, len + 1);
	free(key);
	add_substr(line, *i, value);
	*i += ft_strlen(value) - 1;
}