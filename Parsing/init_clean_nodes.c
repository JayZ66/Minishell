/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_clean_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:14:00 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 09:09:49 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_clean_token	*init_clean_node(char *content, t_type type)
{
	t_clean_token	*token;

	token = (t_clean_token *)ft_malloc(sizeof(t_clean_token));
	if (token == NULL)
	{
		perror("List has not been created\n");
		exit(EXIT_FAILURE);
	}
	token->content = ft_strdup(content);
	ft_free(content);
	if (token->content == NULL)
	{
		ft_free(token);
		perror("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_clean_token	*lst_clean_last(t_clean_token *token)
{
	if (token == NULL)
	{
		perror("Token node is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	return (token);
}

void	add_clean_back(t_clean_token **token, t_clean_token *new)
{
	t_clean_token	*last;

	if (!(*token))
		*token = new;
	else
	{
		last = lst_clean_last(*token);
		last->next = new;
	}
}

void	print_clean_lst(t_clean_token *token)
{
	t_clean_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Chaque node clean content : %s\n", tmp->content);
		printf("Chaque node clean type content : %u\n", tmp->type);
		tmp = tmp->next;
	}
}

void	free_that_clean_lst(t_clean_token **token)
{
	t_clean_token	*tmp;

	if (!(*token))
	{
		ft_free(token);
		perror("Clean lst is empty, can't free\n");
		exit(EXIT_FAILURE);
	}
	while (*token)
	{
		tmp = (*token)->next;
		if ((*token)->content)
			ft_free((*token)->content);
		ft_free(*token);
		*token = tmp;
	}
	*token = NULL;
}
