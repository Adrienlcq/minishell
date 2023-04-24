/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 18:45:03 by adlecler          #+#    #+#             */
/*   Updated: 2023/04/24 15:20:53 by adlecler         ###   ########.fr       */
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

    /* printf("Commande = %s\n",node_token->token); */
    if (!node_token->next) // si pas d'argument apres unset
        return ;
    node_token = node_token->next; // 1er arg apres unset
    /* printf("1er ARG (node_token->token) = %s\n",node_token->token); // premier arg
    printf("node_token->next->token = %s\n", node_token->next->token); // deuxieme arg ? */
    while (node_token) // tant que arg existe
    {
        arg = node_token->token; // arg devient le nom de la variable d'environnement a unset
        while (ft_strcmp(arg, node_env->key) != 0) // tant que arg != key
        {
            if (node_env->next) //si la prochaine ligne des var d'env existe
                node_env = node_env->next; // on passe a la prochaine ligne des variables d'environnement
            else
                break ;
            if (ft_strcmp(arg, node_env->key) == 0)
            {
                remove_node(env, node_env);
                break ;
                /* remove_node(t_env *env, t_env_node *node) //(la liste, le noeud a supprimer) */
            }
        }
        if (node_token->next) // si encore un arg apres unset
        {
            node_token = node_token->next; // node_token = prochain arg apres unset
            node_env = env->first; // on remet node_env a la premiere ligne des variables d'environnement
            //arg = node_token->token; // arg prend la valeur du prochain argument apres unset
        }
        else
            return ;
    }
}
