/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:37:26 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/25 19:27:08 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_exec(t_token *token, t_env *env)
{
    (void)env;
    t_token_node *node;

    node = token->first;
    if (ft_strncmp(node->token, "pwd", 3) == 0)
        ft_pwd();
    else if (ft_strncmp(node->token, "env", 3) == 0)
        ft_env(env);
    /* else if (ft_strncmp(node->token, "echo", 4) == 0)
        ft_echo(); */
    return (1);
}
