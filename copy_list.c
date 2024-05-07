/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:09:29 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/06 11:09:52 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_clean_token *copy_lst(t_token *token)
{
	t_clean_token	*clean_list;
	t_clean_token	*block_start;
	t_clean_token	*new;
	char			*content;

	clean_list = NULL;
	content = NULL;
	while (token)
	{
		block_start = token;
		while (token && token->type != PIPE)
		{
			if (token->type == INPUT || token->type == HERE_DOC)
			{
				content = ft_strdup(token->content);
				new = init_clean_node(content, token->type);
				add_clean_back(&clean_list, new);
				free(content);
			}
			token = token->next;
		}
		token = block_start;
		while (token && token->type != PIPE)
		{
			if (token->type == ARG)
			{
				content = ft_strdup(token->content);
				new = init_clean_node(content, token->type);
				add_clean_back(&clean_list, new);
				free(content);
			}
			token = token->next;
		}
		token = block_start;
		while (token && token->type != PIPE)
		{
			if (token->type == OUTPUT || token->type == APPEND)
			{
				content = ft_strdup(token->content);
				new = init_clean_node(content, token->type);
				add_clean_back(&clean_list, new);
				free(content);
			}
			token = token->next;
		}
		if (token != NULL)
		{
			if (token->type == PIPE)
			{
				content = ft_strdup("|");
				new = init_clean_node(content, token->type);
				add_clean_back(&clean_list, new);
				free(content);
			}
			token = token->next;
		}
	}
	return (clean_list);
}

t_clean_token *copy_lst(t_token *token)
{
    // t_token *head = token;
    t_clean_token *clean_list = NULL;
    char *content = NULL;

    while (token != NULL)
    {
        t_token *block_start = token; // Pointeur de départ pour le bloc actuel

        while (token != NULL && token->type != PIPE)
        {
            if (token->type == INPUT || token->type == HERE_DOC)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Ajouter les arguments pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == ARG)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Ajouter les sorties pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == OUTPUT || token->type == APPEND)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Passer au prochain bloc s'il y en a un
        if (token!= NULL)
        {
			if (token->type == PIPE)
			{
				content = ft_strdup("|");
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
			}
            token = token->next; // Avancer pour sauter le pipe
        }
    }
    return clean_list;
}
