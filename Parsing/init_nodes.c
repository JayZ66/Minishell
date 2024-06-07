/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:31 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 09:10:44 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_node(char *content, t_type type)
{
	t_token	*token;

	token = (t_token *)ft_malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("List has not been created\n");
		exit(EXIT_FAILURE);
	}
	token->content = ft_strdup(content);
	ft_free(content);
	if (token->content == NULL)
	{
		perror("Memory allocation failde\n");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*init_node_separator(t_type type)
{
	t_token	*token;

	token = (t_token *)ft_malloc(sizeof(t_token));
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
