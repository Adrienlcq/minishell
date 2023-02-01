/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:45:03 by adlecler          #+#    #+#             */
/*   Updated: 2023/02/01 18:57:42 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Le builtin unset est utilisé pour supprimer une ou plusieurs variables
d'environnement ou variables shell définies précédemment. Après l'exécution
de ce builtin, les variables spécifiées ne seront plus accessibles dans
l'environnement actuel du shell. */

/* Il faut parcourir la liste env jusqu'a arg == key.
Supprimer le noeud qui contient key=value a unset */

#include "../../includes/minishell.h"

/* -------------------------------------------------------------------------- */

/* UNSET AVEC UN SEUL ARG */

/* void ft_unset(t_env *env, t_token *token) //env est une copie de envp qui contient les variables d'environnement
{
    t_env_node *node_env; //on cree une variable node de type t_env_node
    t_token_node *node_token;
    char *arg;

    node_env = env->first; //node_env = premiere ligne des varibles d'environnement
    node_token = token->first; // token->first = unset
    arg = "empty";

    if (!node_token->next) // si pas d'argument apres unset
        return ;
    else
        arg = node_token->next->token; // arg devient le nom de la variable d'environnement a unset
    while (ft_strcmp(arg, node_env->key) != 0) // tant que arg !=  key
        node_env = node_env->next; // on passe a la prochaine ligne des variables d'environnement
    //appel fct remove_node 
    //void	remove_node(t_env *env, t_env_node *node) //(la liste, le noeud a supprimer)
    remove_node(env, node_env);
} */


/* UNSET AVEC PLUSIEURS ARG */
/* unset + variable d'env qui n'existe pas = seg fault */

void ft_unset(t_env *env, t_token *token) //env est une copie de envp qui contient les variables d'environnement
{
    t_env_node *node_env; //on cree une variable node de type t_env_node
    t_token_node *node_token;
    char *arg;

    node_env = env->first; //node_env = premiere ligne des varibles d'environnement
    node_token = token->first; // token->first = unset
    arg = "empty";

    if (!node_token->next) // si pas d'argument apres unset
        return ;
    else
        arg = node_token->next->token; // arg devient le nom de la variable d'environnement a unset

    while (node_token->next) // tant que arg apres unset existe
    {
        while (ft_strcmp(arg, node_env->key) != 0) // tant que arg != key
            node_env = node_env->next; // on passe a la prochaine ligne des variables d'environnement
        //appel fct remove_node 
        /* void	remove_node(t_env *env, t_env_node *node) //(la liste, le noeud a supprimer) */
        remove_node(env, node_env);
        if (node_token->next->next) // si encore un arg apres unset
        {
            node_token = node_token->next; // node_token = prochain arg apres unset
            node_env = env->first; // on remet node_env a la premiere ligne des varibles d'environnement
            arg = node_token->next->token; // arg prend la valeur du prochain argument apres unset
        }
        else
            return ;
    }
}