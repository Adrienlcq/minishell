/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 18:22:46 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/30 19:58:42 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* PROBLEME AVEC LES TOKEN */

/* void ft_exit(t_token *token)
{
    t_token_node *current = token->first->next;
    t_token_node *temp = current;
    int arg = 0;
    
    while (temp->next != NULL)
    {
        arg += 1;
        printf("arg = %d\n", arg);
        temp = temp->next;
    }

    if (token == NULL || token->first == NULL)
    {
        printf("exit\n");
        exit(0);
    }
    if (current == NULL || current->token == NULL)
    {
        printf("exit\n");
        exit(0);
    }

    if (!ft_isdigit(current->token))
    {
        printf("exit\nbash: exit: %s: numeric argument required\n", current->token);
        exit(0);
    }

    current = current->next;
    if (current != NULL && current->token != NULL)
    {
        printf("exit\nbash: exit: too many arguments\n");
        return;
    }

    int exit_status = ft_atoi(token->first->next->token);
    printf("exit\n");
    exit(exit_status);
} */


void ft_exit(t_token *token)
{
    t_token_node *current = token->first->next;
    int exit_status = 0;
    
    if (current != NULL) {
        if (!ft_isdigit(current->token))
        {
            printf("exit\nbash: exit: %s: numeric argument required\n", current->token);
            exit(1);
        }
        exit_status = ft_atoi(current->token);
        current = current->next;
    }

    if (current != NULL) {
        printf("exit\nbash: exit: too many arguments\n");
        return ;
        //exit(1);
    }
    printf("exit\n");
    exit(exit_status);
}
