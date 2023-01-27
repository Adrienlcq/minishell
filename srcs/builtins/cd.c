/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 19:25:59 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/27 19:27:09 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_cd(t_token *token)
{
    t_token_node *node;
    //t_token_node *current;

    node = token->first; /* node = cd */
    if (node->next == NULL) /* il n'y a pas d'argument apres cd */
    {
        printf("\n");
        return 1;
    }
    if (node->next->next != NULL) /* il y a plus d'1 argument apres cd */
    {
        printf("bash: cd: too many arguments\n");
        return 1;
    }

    /* Check if the directory path is an absolute path or a relative path */
    int isAbsolute = 0;
    if ((ft_strncmp(node->next->token, "/", 1)) || (ft_strncmp(node->next->token, "./", 2)))
    {
        isAbsolute = 1;
    }

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return 1;
    }

    char new_dir[1024];

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

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        return 1;
    }
    printf("Current working directory: %s\n", cwd);
    return 0;
}
