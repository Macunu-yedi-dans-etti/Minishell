#include "minishell.h"

static int read_history_file(const char *filename)
{
    int fd;
    
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: history file could not be opened\n", 2);
        return -1;
    }
    close(fd);
    return 0;
}

int main(int ac, char **av, char **env)
{
    char *input;
    char **v1env;
    (void)ac;
    (void)av;
    t_token *tokens;
    t_cmd *cmds;

    v1env = copy_env(env);

    if (read_history_file(".minishell_history") == 0)
        read_history(".minishell_history");

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
            add_history(input);

        tokens = lexer(input);
        cmds = parser(tokens);
        exec_cmds(cmds, &v1env);

        free(input);
        free_input_token(tokens);
        free_cmds(cmds);
    }

    write_history(".minishell_history");
    return 0;
}

