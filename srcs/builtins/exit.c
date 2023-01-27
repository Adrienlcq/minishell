/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:46 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/27 18:04:03 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* PROBLEME AVEC LES TOKEN, BUILTIN IMPOSSIBLE POUR L'INSTANT */



/* checker pour plusieurs arg -> exit si arg 1 est alpha () / pas exit si arg 1 est numeric*/
/* checker pour 1 arg alpha -> bash: exit: [...]: numeric argument required + exit */
/* checker pour 1 arg numeric -> exit */
/* checker pour 0 argument -> exit */

#include "../../includes/minishell.h"

void    ft_exit(t_token *token)
{
    t_token_node *current;
    //t_token_node *tail;
    //int arg = 0;
    
    current = token->first;
    //tail = token->last;
    //printf("current->next->token : %s\n", current->next->token);
    
    /* printf("1er argument : %s\n", current->token);
    printf("Dernier argument : %s\n", token->last->token); */

    /* Nombre d'arguments infini | Probleme avec les token */
    /* while (current->token != NULL)
    {
        arg += 1;
        printf("arg = %d\n", arg);
        current->token = current->next->token;
    } */

    if (current->next->token == NULL) /* Si pas d'arg alors exit(0) */
    {
        printf("exit\n");
        exit(0);
    }
    else if ((current->next->token != NULL) && (ft_isdigit(current->next->token) == 0)) /* Si arg 1 non numeric */
    {
       printf("exit\nbash: exit: %s: numeric argument required\n", current->next->token);
       exit(0);
    }
    else if ((ft_isdigit(current->next->token) == 1) && (current->next->next->token != NULL)) /* Si arg 1 numeric && arg 2 existe */
    {
       printf("exit\nbash: exit: too many arguments\n");
       return ;
    }
    else if ((ft_isdigit(current->next->token) == 1) && (current->next->next->token == NULL)) /* Si arg 1 numeric && arg 2 n'existe pas */
    {
       printf("exit\n");
       exit(ft_atoi(current->next->token)); /* Si 1 seul arg numeric alors exit(arg) */
    }
}
