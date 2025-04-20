#include "minishell.h"

/*
static void	exit_error(char *cmd, char **s_cmd, int code)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(cmd, 2);
	ft_free(s_cmd);
	//exit(code);
}
*/
/*
static int read_checker(int fd, )
{
		if (access(av[1], R_OK) == -1 && access(av[1], F_OK) != -1)
		{
			ft_putstr_fd(av[1], 2);
			ft_putendl_fd(": Permission denied ", 2);
			exit (1);
		}
		ft_putstr_fd(av[1], 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit (1);
}
*/

static void	exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

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
		ft_err(s_cmd[0]);
		ft_free(s_cmd);
		return;
	}
	if (execve(path, s_cmd, env) == -1)
	{
		ft_err(s_cmd[0]);
		ft_free(s_cmd);
	}
}

int main(int ac, char **av, char **env)
{
	char *input;
	(void) ac;
	(void) av;
	/*int fd;

	fd = open(".minishell_history", O_RDONLY, 0777);

	if (read_checker(fd))*/
	read_history(".minishell_history"); //geçmişi okuyan fonksiyon

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break;
		}

		if (*input)
			add_history(input); // lineda veri girdisi olursa bunu geçmişe ekle 

		//printf("Komut: %s\n", input);
		exec(input, env);
		free(input);
	}

	write_history(".minishell_history"); // geçmişi bu dosyada tutuyoruz bunu kullanıcaz ileride history komutu için
	return 0;
}

