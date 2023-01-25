#include "../../includes/minishell.h"

void	token_init_list(t_token *token)
{
	token->first = NULL;
	token->last = NULL;
}

int	token_list_pushBack(t_token *token, char *value)
{
	t_token_node *new;

	new = malloc(sizeof(t_token_node));
	if (new == NULL)
		return (0);
	new->token = ft_strdup(value);
	if (new->token == NULL)
		return (0);
	new->is_piped = 0; // On initialise toutes les autres variables a 0 vu qu'on a pas encore checker la value
	new->is_quoted = 0;
	new->type = 0;
	new->prev = token->last;
	new->next = NULL;
	if (token->last)
		token->last->next = new;
	else
		token->first = new;
	token->last = new;
	return (1);
}

int	token_list_pushFront(t_token *token, char *value)
{
	t_token_node *new;

	new = malloc(sizeof(t_token_node));
	if (new == NULL)
		return (0);
	new->token = ft_strdup(value);
	if (new->token == NULL)
		return (0);
	new->is_piped = 0;
	new->is_quoted = 0;
	new->type = 0;
	new->prev = NULL;
	new->next = token->first;
	token->first = new;
	if (token->last == NULL)
		token->last = new;
	return (1);
}

int	token_list_popBack(t_token *token)
{
	t_token_node *tmp;

	tmp = token->last;
	if (!tmp)
		return (0);
	token->last = tmp->prev;
	if (token->last)
		token->last->next = NULL;
	else
		token->first = NULL;
	free(tmp->token);
	free(tmp);
	return (1);
}

int	token_list_popFront(t_token *token)
{
	t_token_node *tmp;

	tmp = token->first;
	if (!tmp)
		return (0);
	token->first = tmp->next;
	if (token->first)
		token->first->prev = NULL;
	else
		token->last = NULL;
	free(tmp->token);
	free(tmp);
	return (1);
}

void	token_list_erase_node(t_token *token, t_token_node *node)
{
	t_token_node *tmp;

	tmp = node;
	if (node->prev && node->next)
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(tmp->token);
		free(tmp);
		tmp = NULL;
	}
	else if (!node->prev)
	{
		token->first = node->next;
		node->next->prev = NULL;
		free(tmp->token);
		free(tmp);
		tmp = NULL;
	}
	else if (!node->next)
	{
		token->last = node->prev;
		node->prev->next = NULL;
		free(tmp->token);
		free(tmp);
		tmp = NULL;
	}
}

void	clear_token(t_token *token)
{
	t_token_node *tmp;

	tmp = token->first;
	while (tmp)
	{
		token->first = tmp->next;
		free(tmp->token);
		free(tmp);
		tmp = token->first;
	}
	tmp = NULL;
}

void	print_token_debug(t_token *token)
{
	for (t_token_node *node = token->first; node; node = node->next)
		printf("token: %s\nis_quoted: %d\nis_piped: %d\ntype: %d\n--------------------------\n", node->token, node->is_quoted, node->is_piped, node->type);
}