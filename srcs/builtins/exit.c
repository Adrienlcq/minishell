/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:46 by adlecler          #+#    #+#             */
/*   Updated: 2023/04/27 16:58:46 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* PROBLEME AVEC LES TOKEN */

/* PROBLEME AVEC EXIT SEUL QUAND ON FAIT UNE AUTRE COMMANDE AVANT (seg fault core dumped) */

void ft_exit(t_token *token)
{
    t_token_node *current = token->first->next;
    int exit_status = 0;
    
    if (current != token->last)
    {
        printf("exit\n");
        exit(1);
    }
    
    if (current != NULL)
    {
        if (!ft_isdigit(current->token))
        {
            printf("exit\nbash: exit: %s: numeric argument required\n", current->token);
            exit(1);
        }
        exit_status = ft_atoi(current->token);
        current = current->next;
    }

    if (current != NULL)
    {
        printf("exit\nbash: exit: too many arguments\n");
        return ;
    }
    printf("exit\n");
    exit(exit_status);
}
