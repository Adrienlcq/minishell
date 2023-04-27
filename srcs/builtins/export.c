/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:28:05 by adlecler          #+#    #+#             */
/*   Updated: 2023/04/27 16:56:33 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Le builtin export permet de définir une variable d'environnement pour
le shell courant et ses sous-processus. Une fois définie, cette variable
peut être utilisée par les autres programmes exécutés par le shell. */

/* Pas besoin de gerer export -p */

#include "../../includes/minishell.h"

int    list_pushBack_export(t_env *env, char *value)
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
    if (new->key == NULL)
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

void display_env(t_env *env)
{
    t_env_node  *node = env->first;
    
    while (node)
    {
        if (!node->value)
            printf("declare -x %s\n", node->key);
        else
            printf("declare -x %s=%s\n", node->key, node->value);
        node = node->next;
    }
}

void ft_export(t_env *env, t_token *token) //env est une copie de envp qui contient les variables d'environnement
{
    t_token_node *node_token; //mon argument
    char *arg;

    node_token = token->first; // token->first = export
    arg = "empty";

    if (!node_token->next) // si pas d'argument apres export
        display_env(env);

    node_token = node_token->next; // 1er arg apres export
    while (node_token) // tant que mon argument existe (variable a export)
    {
        arg = node_token->token; // arg devient le nom de la variable d'environnement a export
        if(arg[0] >= 48 && arg[0] <= 57) // si arg commence par un chiffre
            printf("export: not an identifier: %s\n", arg);
        else
            list_pushBack_export(env, arg);
        
        if (node_token->next) // si encore un arg apres l'arg actuel
            node_token = node_token->next; // node_token = prochain arg apres unset
        else
            return ;
    }
}
