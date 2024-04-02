/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:02:21 by romlambe          #+#    #+#             */
/*   Updated: 2024/04/02 23:49:21 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*clean_arg(t_token **token)
// {
// 	int	i;
// 	char	*cmd;
// 	t_token	*new;
// 	t_token	*temp;
// 	t_token *result;

// 	new = NULL;
// 	temp = *token;
// 	result = NULL;
// 	while (temp != NULL)
// 	{
// 		i = 0;
// 		while (temp->content[i] == ' ')
// 			i++;
// 		if (temp->type == ARG)
// 		{
// 			cmd = ft_strdup((*token)->content);
// 			printf("commande complète: %s\n", cmd);
// 			new = init_node(cmd, ARG);
// 			add_back(&result, new);
// 		}
// 		temp = temp->next;
// 	}
// 	return (result);
// }

// t_token *clean_arg(t_token **token)
// {
//     t_token *current = *token; // Pointeur vers le début de la liste
//     t_token *result = NULL; // Pointeur vers le début de la nouvelle liste
//     t_token *arg_node = NULL; // Pointeur vers le début des noeuds d'argument
//     char *arg_str = NULL; // Chaîne pour stocker l'argument complet

//     while (current != NULL)
//     {
//         if (current->type == ARG)
//         {
//             // Si on commence un nouvel argument, initialiser la chaîne et le noeud d'argument
//             if (arg_node == NULL)
//             {
//                 arg_node = current;
//                 arg_str = ft_strdup(current->content);
//             }
//             else
//             {
//                 // Concaténer le contenu de l'argument au string complet
//                 char *temp = ft_strjoin(arg_str, " ");
//                 free(arg_str);
//                 arg_str = ft_strjoin(temp, current->content);
//                 free(temp);
//             }
//         }
//         else
//         {
//             // Si on rencontre un autre type de noeud, ajouter l'argument complet à la nouvelle liste
//             if (arg_node != NULL)
//             {
//                 t_token *new_arg_node = init_node(arg_str, ARG);
//                 add_back(&result, new_arg_node);
//                 arg_node = NULL; // Réinitialiser le noeud d'argument
//                 free(arg_str);
//                 arg_str = NULL;
//             }
//             add_back(&result, current); // Ajouter le noeud actuel à la nouvelle liste
//         }
//         current = current->next; // Passer au prochain noeud
//     }

//     // Ajouter le dernier argument complet à la nouvelle liste
//     if (arg_node != NULL)
//     {
//         t_token *new_arg_node = init_node(arg_str, ARG);
//         add_back(&result, new_arg_node);
//         free(arg_str);
//     }

//     // Libérer l'ancienne liste

//     *token = NULL; // Réinitialiser le pointeur de l'ancienne liste à NULL

//     return result; // Retourner le début de la nouvelle liste
// }


t_token *clean_arg(t_token **token)
{
    t_token *current = *token; // Pointeur vers le début de la liste
    t_token *result = NULL; // Pointeur vers le début de la nouvelle liste
    t_token *arg_node = NULL; // Pointeur vers le début des noeuds d'argument
    char *arg_str = NULL; // Chaîne pour stocker l'argument complet

    while (current != NULL)
    {
        if (current->type == ARG)
        {
            // Si on commence un nouvel argument, initialiser la chaîne et le noeud d'argument
            if (arg_node == NULL)
            {
                arg_node = current;
                arg_str = ft_strdup(current->content);
            }
            else
            {
                // Concaténer le contenu de l'argument au string complet
                char *temp = ft_strjoin(arg_str, " ");
                free(arg_str);
                arg_str = ft_strjoin(temp, current->content);
                free(temp);
            }
        }
        else
        {
            // Si on rencontre un autre type de noeud, ajouter l'argument complet à la nouvelle liste
            if (arg_node != NULL)
            {
                t_token *new_arg_node = init_node(arg_str, ARG);
                add_back(&result, new_arg_node);
                arg_node = NULL; // Réinitialiser le noeud d'argument
                free(arg_str);
                arg_str = NULL;
            }
            add_back(&result, current); // Ajouter le noeud actuel à la nouvelle liste
        }
        current = current->next; // Passer au prochain noeud
    }

    // Ajouter le dernier argument complet à la nouvelle liste
    if (arg_node != NULL)
    {
        t_token *new_arg_node = init_node(arg_str, ARG);
        add_back(&result, new_arg_node);
        free(arg_str);
        arg_node = NULL; // Réinitialiser le noeud d'argument
    }

    // Libérer l'ancienne liste

    *token = NULL; // Réinitialiser le pointeur de l'ancienne liste à NULL

    return result; // Retourner le début de la nouvelle liste
}
