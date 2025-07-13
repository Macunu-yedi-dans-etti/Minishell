NAME = minishell

SRCS = minishell.c \
       src/signal.c \
	   src/input_message.c\
	   src/parser/tokenizer.c\
	   src/parser/parser.c\
	   src/executor/executor.c\
	   src/builtin/builtin_check.c\
	   src/builtin/cd/builtin_cd.c\
	   src/builtin/cd/cd_utils.c\
	   src/builtin/builtin_echo.c\
	   src/builtin/builtin_env.c\
	   src/builtin/builtin_exit.c\
	   src/builtin/builtin_export.c\
	   src/builtin/builtin_unset.c\
	   src/builtin/builtin_pwd.c\
	   src/builtin/run_builtin.c\
	   src/redirect/redirect_handler.c\
	   src/redirect/heredoc_handler.c\
	   src/expander/expander.c\
	   src/mini_error.c\
       general_utility/ft_free.c \
       general_utility/utility.c \
	   general_utility/resolve_path.c\
       enviroment_utility/enviroment.c\
	   enviroment_utility/mini_setenv_line.c\

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -g -Wall -Wextra -Werror
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re

