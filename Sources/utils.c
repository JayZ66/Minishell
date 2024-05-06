/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 10:27:43 by marvin            #+#    #+#             */
/*   Updated: 2024/03/22 10:27:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
En résumé, l'utilisation d'un pointeur double vous permet de modifier le 
pointeur lui-même, pas seulement la valeur à laquelle il pointe. Cela vous 
permet de réinitialiser correctement le pointeur token à NULL après avoir 
libéré la mémoire de la liste chaînée.
*/
void	free_that_lst(t_token **token)
{
	t_token	*tmp;

	if (!(*token))
	{
		perror("Lst is empty, can't free\n");
		exit(EXIT_FAILURE);
	}
	while (*token)
	{
		tmp = (*token)->next;
		free((*token)->content);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}

// t_token	*init_node(char *content, Token_type type)
// {
// 	t_token	*token;

// 	token = (t_token *)malloc(sizeof(t_token));
// 	if (token == NULL)
// 	{
// 		perror("List has not been created\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	token->content = ft_strdup(content);
// 	if (token->content == NULL)
// 	{
// 		perror("Memory allocation failde\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	token->type = type;
// 	token->next = NULL;
// 	return (token);
// }

t_token	*lst_last(t_token *token)
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

void	add_back(t_token **token, t_token *new)
{
	t_token	*last;

	if (!token)
	{
		perror("List is empty\n");
		exit(EXIT_FAILURE);
	}
	if (!(*token))
		*token = new;
	else
	{
		last = lst_last(*token);
		last->next = new;
	}
}
