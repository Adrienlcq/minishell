/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 18:37:26 by adlecler          #+#    #+#             */
/*   Updated: 2023/04/24 16:43:12 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_exec(t_token *token, t_env *env)
{
    (void)env;
    t_token_node *node;

    node = token->first;
    if (ft_strcmp(node->token, "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(node->token, "env") == 0)
        ft_env(env);
    else if (ft_strcmp(node->token, "echo") == 0)
        ft_echo(token);
    else if (ft_strcmp(node->token, "exit") == 0)
        ft_exit(token);
    else if (ft_strcmp(node->token, "cd") == 0)
        ft_cd(token);
    else if (ft_strcmp(node->token, "unset") == 0)
        ft_unset(env, token);
    else if (ft_strcmp(node->token, "export") == 0)
        ft_export(env, token);
    return (1);
}
