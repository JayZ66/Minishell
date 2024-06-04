/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_nodes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:05:31 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/04 16:38:24 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*init_node(char *content, Token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("List has not been created\n");
		exit(EXIT_FAILURE);
	}
	token->content = ft_strdup(content);
	if (token->content == NULL)
	{
		perror("Memory allocation failde\n");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_token	*init_node_separator(Token_type type)
{
	t_token	*token;

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
