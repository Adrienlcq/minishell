/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlecler <adlecler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:28:05 by adlecler          #+#    #+#             */
/*   Updated: 2023/01/31 18:42:47 by adlecler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Le builtin export permet de définir une variable d'environnement pour
le shell courant et ses sous-processus. Une fois définie, cette variable
peut être utilisée par les autres programmes exécutés par le shell. */

/* Il est possible de définir une variable d'environnement sans utiliser
la commande "export" en utilisant la fonction "setenv" du C */

/* Le remplacement de la fonction setenv peut être effectué en utilisant
putenv ou en manipulant directement la table des variables d'environnement
avec getenv, malloc, realloc et strcpy */

/* Notez que la modification de la table des variables d'environnement
n'aura un effet que sur le processus en cours et ne sera pas transmise à
ses sous-processus. */

#include "../../includes/minishell.h"

int ft_export(t_env *env)
{
    
}
