/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:28:02 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/26 17:22:16 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* probleme si : echo -n[...] || echo -n */
/* echo -n[...] OK avec && ft_strlen (L28)*/
/* echo -n OK avec le if (L32) */

#include "../../includes/minishell.h"

void ft_echo(t_token *token)
{
    int first_token_is_option;
    t_token_node *node;
    t_token_node *current;

    node = token->first;
    first_token_is_option = 0;
    if (node->next != NULL)
    {
        if ((ft_strncmp(node->next->token, "-n", 2) == 0) && (ft_strlen(node->next->token) == 2))
        {
            node = node->next;
            if (node->next == NULL) /* Dans le cas : echo -n */
                return ; /* Ne rien afficher */
            first_token_is_option = 1;
            if (node->next != NULL)
                current = node->next;
        }
    }
    if (first_token_is_option == 0)
        current = node->next;
    while (current != NULL)
    {
        printf("%s", current->token);
        current = current->next;
        if (current != NULL)
            printf(" ");
    }
    if (first_token_is_option == 0)
        printf("\n");
}
