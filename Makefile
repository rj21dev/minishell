NAME		= minishell
SRCS_DIR	= src/
OBJS_DIR	= obj/
INCS_DIR	= include
SRCS_F		= main.c space_pusher.c env.c env_utils.c dollar_expander.c lexer.c quotes_expander.c utils_str.c \
					parser.c parser_utils.c executor.c heredoc.c validator.c builtins.c executor_utils.c ft_export.c \
					ft_export_util.c ft_exit.c	shlv.c executor_utils2.c ft_cd.c util_norm.c
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_F))
OBJS_F		= $(patsubst %.c, %.o, $(SRCS_F))
DEPS_F		= $(patsubst %.c, %.d, $(SRCS_F))
OBJS		= $(addprefix $(OBJS_DIR), $(OBJS_F))
DEPS		= $(addprefix $(OBJS_DIR), $(DEPS_F))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -MMD
LFLAGS		= -Llibft -lft -L/Users/$(USER)/.brew/Cellar/readline/8.1.2/lib -lreadline
LIB			= libft.a
LIB_DIR		= libft/

all: $(NAME)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c
		$(CC) $(CFLAGS) -I$(INCS_DIR) -c $< -o $@

$(OBJS_DIR) :
		mkdir -p $@

$(NAME):  $(OBJS_DIR) $(OBJS) $(LIB_DIR)$(LIB) Makefile
		$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $@

$(LIB_DIR)$(LIB) : ;
		make -C $(LIB_DIR)

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(LIB_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIB_DIR)

re: fclean all

.PHONY:
		all clean fclean re bonus

-include $(DEPS) $(DEPS_B)
