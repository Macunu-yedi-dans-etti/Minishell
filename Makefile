NAME = minishell

SRCS = main/minishell.c \
       main/minishell_setup.c \
       main/minishell_processing.c \
       main/minishell_token_utils.c \
       src/signal.c \
	   src/expander.c\
	   src/mini_error.c\
	   src/input_message.c\
	   src/tokenizer/tokenizer_core.c\
	   src/tokenizer/tokenizer_core2.c\
	   src/tokenizer/tokenizer_utils.c\
	   src/tokenizer/token_quote_utils.c\
	   src/parser/parser.c\
	   src/parser/parser_utils.c\
	   src/parser/parser_utils2.c\
	   src/parser/parse_tokens_utility.c\
	   src/executor/executor_utils.c\
	   src/executor/executor_exec.c\
	   src/executor/executor_process.c\
	   src/executor/executor_builtin.c\
	   src/executor/executor_pipeline.c\
	   src/executor/executor_pipeline_utils.c\
	   src/executor/executor_pipe_utils.c\
	   src/builtin/builtin_check.c\
	   src/builtin/cd/builtin_cd.c\
	   src/builtin/cd/cd_utils.c\
	   src/builtin/cd/cd_error.c\
	   src/builtin/builtin_echo.c\
	   src/builtin/builtin_env.c\
	   src/builtin/builtin_exit.c\
	   src/builtin/export/builtin_export.c\
	   src/builtin/export/export_validation.c\
	   src/builtin/export/export_list.c\
	   src/builtin/export/export_print.c\
	   src/builtin/export/export_utils.c\
	   src/builtin/builtin_unset.c\
	   src/builtin/builtin_pwd.c\
	   src/builtin/run_builtin.c\
	   src/redirect/redirect_handler.c\
	   src/redirect/heredoc_handler/heredoc_handler.c\
	   src/redirect/heredoc_handler/heredoc_handler_utils.c\
       general_utility/ft_free.c \
	   general_utility/ft_free2.c\
       general_utility/utility.c \
	   general_utility/resolve_path.c\
       enviroment_utility/enviroment/enviroment.c\
	   enviroment_utility/enviroment/enviroment2.c\
	   enviroment_utility/mini_setenv_line.c\

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = includes/libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	@make -s -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make -s clean -C $(LIBFT_DIR)

fclean: clean
	@rm -f $(NAME)
	@make -s fclean -C $(LIBFT_DIR)

re: fclean all

leak:
	valgrind --leak-check=full --show-leak-kinds=all --suppressions=valgrind.supp --track-origins=yes -s ./minishell


.PHONY: all clean fclean re

