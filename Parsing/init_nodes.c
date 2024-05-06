/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:31 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/06 14:55:16 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token    *init_node(char *content, Token_type type)
{
    t_token    *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
    {
        perror("List has not been created\n");
        exit(EXIT_FAILURE);
    }
    token->content = ft_strdup(content); // Add token function here !
    if (token->content == NULL)
    {
        perror("Memory allocation failde\n");
        exit(EXIT_FAILURE);
    }
    token->type = type;
    token->next = NULL;
    return (token);
}

t_token    *init_node_separator(Token_type type)
{
    t_token    *token;

    token = (t_token *)malloc(sizeof(t_token));
    if (token == NULL)
    {
        perror("List has not been created\n");
        exit(EXIT_FAILURE);
    }
    token->content = NULL;
    token->type = type;
    token->next = NULL;
    return (token);
}

// void    free_that_lst(t_token **token)
// {
//     t_token    *tmp;

//     if (!(*token))
//     {
//         perror("Lst is empty, can't free\n");
//         exit(EXIT_FAILURE);
//     }
//     while (*token)
//     {
//         tmp = (*token)->next;
//         free((*token)->content);
//         free(*token);
//         *token = tmp;
//     }
//     *token = NULL;
// }
