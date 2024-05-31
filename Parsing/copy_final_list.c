/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_final_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:58:56 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/31 17:43:43 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_final_token *final_clean_node(t_clean_token *token)
{
	t_final_token *final_token = NULL;
    t_final_token  *new = NULL;
	char *content = NULL;

	while (token)
	{
		while (token && (token->type == INPUT || token->type == HERE_DOC))
		{
			if (!token->next || (token->next->type != INPUT && token->next->type != HERE_DOC))
			{
				// content = ft_strdup(token->content);
				// if (!content)
				// {
				// 	free_that_final_lst(&final_token); 
				// 	return (NULL);
				// }
				// t_final_token *new = init_final_node(content, token->type);
				// add_final_back(&final_token, new);
				// free(content);
                handle_input(token, final_token, new, content);
			}
			token = token->next;
		}

		while (token && token->type == CMD)
		{
			content = ft_strdup(token->content);
			if (!content)
			{
				free_that_final_lst(&final_token); 
				return (NULL);
			}
			t_final_token *new = init_final_node(content, token->type);
			add_final_back(&final_token, new);
			free(content);
			token = token->next;
		}

		while (token && (token->type == OUTPUT || token->type == APPEND))
		{
			if (!token->next || token->next->type == PIPE)
			{
				content = ft_strdup(token->content);
				if (!content)
				{
					free_that_final_lst(&final_token); 
					return (NULL);
				}
				t_final_token *new = init_final_node(content, token->type);
				add_final_back(&final_token, new);
				free(content);
			}
			token = token->next;
		}

		if (token && token->type == PIPE)
		{
			content = ft_strdup("|");
			if (!content)
			{
				free_that_final_lst(&final_token); 
				return (NULL);
			}
			t_final_token *new = init_final_node(content, token->type);
			add_final_back(&final_token, new);
			free(content);
			token = token->next;
		}
	}
	return (final_token);
}

void   handle_input(t_clean_token *token, t_final_token *final_token, t_final_token *new, char *content)
{
    content = ft_strdup(token->content);
    if (!content)
    {
        free_that_final_lst(&final_token);
        return ;
    }
    new = init_final_node(content, token->type);
    add_final_back(&final_token, new);
    free(content);
    // return(final_token);
}
























t_final_token	*init_final_node(char *content, Token_type type)
{
	t_final_token	*token;

	token = (t_final_token *)malloc(sizeof(t_final_token));
	if (token == NULL)
	{
		perror("List has not been created\n");
		exit(EXIT_FAILURE);
	}
	token->content = ft_strdup(content);
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
