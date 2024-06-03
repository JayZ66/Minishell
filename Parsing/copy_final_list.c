/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_final_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:58:56 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/03 17:41:57 by romlambe         ###   ########.fr       */
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
	content = ft_strdup(token->content);
	if (!content)
	{
		free_that_final_lst(final_token);
		return (NULL);
	}
	new = init_final_node(content, token->type);
	add_final_back(&final_token, new);
	free(content);
	return (final_token);
}

t_final_token	*handle_final_pipe(t_clean_token *token,
	t_final_token *final_token, t_final_token *new, char *content)
{
	content = ft_strdup("|");
	if (!content)
	{
		free_that_final_lst(final_token);
		return (NULL);
	}
	new = init_final_node(content, token->type);
	add_final_back(&final_token, new);
	free(content);
	return (final_token);
}
