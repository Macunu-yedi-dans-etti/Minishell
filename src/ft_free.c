#include "../minishell.h"


void	ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_stacks(t_token **a_stack)
{
	t_token	*node;

	while (*a_stack)
	{
		node = *a_stack;
		*a_stack = (*a_stack)->next;
		free(node);
	}
	free(a_stack);

}


void free_input_token(t_token *cmds)
{
	t_token *tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		free(tmp);
	}
}

void free_cmds(t_cmd *cmds)
{
	t_cmd *tmp;

	while (cmds)
	{
		tmp = cmds;
		cmds = cmds->next;
		// burada komutun argümanları veya path gibi alanları da serbest bırakabilirsin
		free(tmp);
	}
}

