/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:06:40 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/25 19:25:44 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* NE PAS LIBERER LA MEMOIRE DE LA VAR D'ENV */

int ft_env(t_env *env) //env est une copie de envp qui contient les variables d'environnement
{
    t_env_node *node; //on cree une variable node de type t_env_node

    node = env->first; //node = premiere ligne des varibles d'environnement
    while (node)
    {
        printf("%s=%s\n", node->key, node->value);
        node = node->next;
    }
    return (1);
}
