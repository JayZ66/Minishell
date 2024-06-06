/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_final_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:58:56 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/06 11:15:19 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_final_token	*final_clean_node(t_clean_token *token)
{
	t_final_token	*final_token;
	t_final_token	*new;
	char			*content;

	final_token = NULL;
	new = NULL;
	content = NULL;
	while (token)
	{
		token = manage_input_here_doc(token, &final_token, new, content);
		token = manage_cmd(token, &final_token, new, content);
		token = manage_output_append(token, &final_token, new, content);
		token = manage_pipes(token, &final_token, new, content);
	}
	return (final_token);
}

t_final_token	*handle_nodes(t_clean_token *token,
	t_final_token *final_token, t_final_token *new, char *content)
{
	content = token->content;
	// if (!content)
	// {
	// 	free_that_final_lst(&final_token);
	// 	return (NULL);
	// }
	new = init_final_node(content, token->type);
	// if (!new)
	// {
	// 	free(content);
	// 	free_that_final_lst(&final_token);
	// 	return (NULL);
	// }
	add_final_back(&final_token, new);
	// ft_free(content);
	return (final_token);
}

t_final_token	*handle_final_pipe(t_clean_token *token,
	t_final_token *final_token, t_final_token *new, char *content)
{
	content = "|";
	if (!content)
	{
		free_that_final_lst(&final_token);
		return (NULL);
	}
	new = init_final_node(content, token->type);
	add_final_back(&final_token, new);
	// ft_free(content);
	return (final_token);
}
 