#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

#define CLOSE "\001\033[0m\002"
#define BEGIN(x,y) "\001\033["#x";"#y"m\002"

#endif
