/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:25:59 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/30 19:42:31 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(t_token *token)
{
    t_token_node *node;
    int isAbsolute = 0;
    char cwd[1024];
    char new_dir[1024];

    node = token->first; /* node = cd */
    if (node->next == NULL) /* pas d'argument apres cd */
    {
        if (chdir(getenv("HOME")) != 0) /* aller à $HOME */
        {
            perror("cd");
            return 1;
        }
    }
    else if (node->next->next != NULL) /* plus d'1 argument apres cd */
    {
        printf("bash: cd: too many arguments\n");
        return 1;
    }
    else /* il y a 1 argument apres cd */
    {
        /* Check si le chemin est relatif ou absolu */
        if (node->next->token[0] == '/')
        {
            isAbsolute = 1;
        }

        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("getcwd");
            return 1;
        }

        if (isAbsolute)
        {
            strcpy(new_dir, node->next->token);
        } 
        else
        {
            strcpy(new_dir, cwd);
            strcat(new_dir, "/");
            strcat(new_dir, node->next->token);
        }

        if (chdir(new_dir) != 0)
        {
            perror("cd");
            return 1;
        }
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return 1;
    }
    printf("Current working directory: %s\n", cwd);
    return 0;
}
