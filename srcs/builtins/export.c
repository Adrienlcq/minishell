/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:28:05 by adlecler          #+#    #+#             */
/*   Updated: 2023/04/24 17:09:20 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Le builtin export permet de définir une variable d'environnement pour
le shell courant et ses sous-processus. Une fois définie, cette variable
peut être utilisée par les autres programmes exécutés par le shell. */

#include "../../includes/minishell.h"

void ft_export(t_env *env, t_token *token) //env est une copie de envp qui contient les variables d'environnement
{
    t_token_node *node_token; //mon argument
    char *arg;

    node_token = token->first; // token->first = export
    arg = "empty";

    if (!node_token->next) // si pas d'argument apres export
        return ; //trier les variables d'env par ordre alphabetique !!!!!!!!!!!!!!!

    node_token = node_token->next; // 1er arg apres export
    while (node_token) // tant que mon argument existe (variable a export)
    {
        arg = node_token->token; // arg devient le nom de la variable d'environnement a export
        if(arg[0] >= 48 && arg[0] <= 57) // si arg commence par un chiffre
            printf("export: not an identifier: %s\n", arg);
        else
            list_pushBack(env, arg);
            
        if (node_token->next) // si encore un arg apres l'arg actuel
            node_token = node_token->next; // node_token = prochain arg apres unset
        else
            return ;
    }
}
