#include "../../includes/minishell.h"

void    env_init_list(t_env *env)
{
    env->first = NULL;
    env->last = NULL;
}

int    list_pushBack(t_env *env, char *value)
{
    t_env_node  *new;
    char        **tab;

    new = malloc(sizeof(t_env_node));
    if (new == NULL)
        return (0);
    tab = ft_split(value, '=');
    if (tab == NULL)
        return (0);
    new->key = ft_strdup(tab[0]);
    new->value = ft_strdup(tab[1]);
    if (new->key == NULL || new->value == NULL)
	{
		ft_free_tab(tab);
        return (0);
	}
    new->prev = env->last;
    new->next = NULL;
    if (env->last)
        env->last->next = new;
    else
        env->first = new;
    env->last = new;
	ft_free_tab(tab);
    return (1);
}

int    list_pushFront(t_env *env, char *value)
{
    t_env_node  *new;
    char        **tab;

    new = malloc(sizeof(t_env_node));
    if (new == NULL)
        return (0);
    tab = ft_split(value, '=');
    if (tab == NULL)
        return (0);
    new->key = ft_strdup(tab[0]);
    new->value = ft_strdup(tab[1]);
    if (new->key == NULL || new->value == NULL)
    {
        ft_free_tab(tab);
        return (0);
    }
    new->prev = NULL;
    new->next = env->first;
    env->first = new;
    if (env->last == NULL)
        env->last = new;
    ft_free_tab(tab);
    return (1);
}

int list_popBack(t_env *env)
{
    t_env_node *tmp;

    tmp = env->last;
    if (!tmp)
        return (0);
    env->last = tmp->prev;
    if (env->last)
        env->last->next = NULL;
    else
        env->first = NULL;
    free(tmp->key);
    free(tmp->value);
    free(tmp);
    return (1);
}

int list_popFront(t_env *env)
{
    t_env_node *tmp;

    tmp = env->first;
    if (!tmp)
        return (0);
    env->first = tmp->next;
    if (env->first)
        env->first->prev = NULL;
    else
        env->last = NULL;
    free(tmp->key);
    free(tmp->value);
    free(tmp);
    return (1);
}

void    clear_env(t_env *env)
{
    t_env_node *tmp;

    tmp = env->first;
    while (tmp)
    {
        env->first = tmp->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        tmp = env->first;
    }
    tmp = NULL;
}

/* supprimer un noeud de la liste env doublement liee */
void	remove_node(t_env *env, t_env_node *node) //(la liste, le noeud a supprimer)
{
	if (!env || !node)
		return ;
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	if (env->first == node)
		env->first = node->next;
	if (env->last == node)
		env->last = node->prev;
	free(node->key);
	free(node->value);
	free(node);
}

void    print_env_debug(t_env *env)
{
    for (t_env_node *node = env->first; node; node = node->next)
        printf("%s=%s\n", node->key, node->value);
}
