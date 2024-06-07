/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_final_nodes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:00:44 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 09:10:36 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_final_token	*init_final_node(char *content, t_type type)
{
	t_final_token	*token;

	token = (t_final_token *)ft_malloc(sizeof(t_final_token));
	if (token == NULL)
	{
		perror("List has not been created\n");
		exit(EXIT_FAILURE);
	}
	token->content = content;
	if (token->content == NULL)
	{
		perror ("Memory allocation failed\n");
		exit (EXIT_FAILURE);
	}
	token->type = type;
	token->next = NULL;
	return (token);
}

t_final_token	*lst_final_last(t_final_token	*token)
{
	if (token == NULL)
	{
		perror ("Token node is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token->next)
		token = token->next;
	return (token);
}

void	add_final_back(t_final_token **token, t_final_token *new)
{
	t_final_token	*last;

	if (!(*token))
		*token = new;
	else
	{
		last = lst_final_last(*token);
		last->next = new;
	}
}

void	print_final_lst(t_final_token *token)
{
	t_final_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Chaque node finale content : %s\n", tmp->content);
		printf("Chaque node finale type content : %u\n", tmp->type);
		tmp = tmp->next;
	}
}
