#include "minishell.h"

static void add_token(t_token **head, char *value, t_token_type type)
{
	t_token *new = malloc(sizeof(t_token));
	new->value = value;
	new->type = type;
	new->next = NULL;

	if (!*head)
		*head = new;
	else
	{
		t_token *temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}

t_token *lexer(const char *input)
{
	t_token *tokens;
	int i;
	int start;

	tokens = NULL;
	i = 0;

	while (input[i])
	{
		if (input[i] == ' ')
		{
			i++;
			continue;
		}
		else if (input[i] == '|')
			add_token(&tokens, ft_strdup("|"), T_PIPE);
		else if (input[i] == '>')
			add_token(&tokens, ft_strdup(">"), T_REDIR_OUT);
		else if (input[i] == '<')
			add_token(&tokens, ft_strdup("<"), T_REDIR_IN);
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '|' && input[i] != '>' && input[i] != '<')
				i++;
			add_token(&tokens, ft_substr(input, start, i - start), T_WORD);
			continue;
		}
		i++;
	}
	return tokens;
}
/*
void print_tokens(t_token *head)
{
	while (head)
	{
		printf("TOKEN: %-10s | TYPE: %d\n", head->value, head->type);
		head = head->next;
	}
}
*/
