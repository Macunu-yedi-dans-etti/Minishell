#include "minishell.h"

/* Hata mesajlarını daha anlamlı hale getirmek için */
static void exit_error(char *cmd, char **s_cmd)
{
    ft_putstr_fd("minishell: command not found: ", 2);
    ft_putendl_fd(cmd, 2);
    ft_free(s_cmd);
}

/* Dosya okuma kontrolünü daha güvenli yapmak için open kullanabiliriz */
static int read_history_file(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        ft_putstr_fd("minishell: history file could not be opened\n", 2);
        return -1;
    }
    close(fd);
    return 0;
}

static void exec(char *cmd, char **env)
{
    char **s_cmd;
    char *path;
    pid_t pid;

    if (!cmd)
    {
        ft_putendl_fd("minishell: empty command", 2);
        return;
    }

    s_cmd = ft_split(cmd, ' ');
    if (!s_cmd || !s_cmd[0])
    {
        ft_putendl_fd("minishell: invalid command", 2);
        ft_free(s_cmd);
        return;
    }

    if (ft_strncmp(s_cmd[0], "exit", 4) == 0)
    {
        if (build_exit(s_cmd) != 0)
        {
            ft_free(s_cmd);
            return;
        }
    }

    path = paths(s_cmd[0], env);
    if (!path)
    {
        exit_error(s_cmd[0], s_cmd); // Hatalı komut için error mesajı
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        if (execve(path, s_cmd, env) == -1)
        {
            exit_error(s_cmd[0], s_cmd); // execve hatası
            write_history(".minishell_history");
            exit(127); // 127 komut bulunamadığında yaygın olarak kullanılır
        }
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
    }
    else
        perror("minishell: fork failed");

    ft_free(s_cmd);
}

int main(int ac, char **av, char **env)
{
    char *input;
    (void) ac;
    (void) av;

    /* Geçmiş dosyasını okuma */
    if (read_history_file(".minishell_history") == 0)
        read_history(".minishell_history"); // geçmişi okur

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
            add_history(input); // Lineda veri girdisi olursa bunu geçmişe ekle

        exec(input, env);  // Komutları çalıştır
        free(input);
    }

    write_history(".minishell_history"); // Geçmişi dosyaya yaz
    return 0;
}

