/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_final_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 15:14:58 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/01 15:19:31 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_clean_token	*manage_input_here_doc(t_clean_token *token,
	t_final_token **final_token, t_final_token *new, char *content)
{
	while (token && (token->type == INPUT || token->type == HERE_DOC))
	{
		if (!token->next || (token->next->type != INPUT
				&& token->next->type != HERE_DOC))
			*final_token = handle_nodes(token, *final_token, new, content);
		token = token->next;
	}
	return (token);
}

t_clean_token	*manage_cmd(t_clean_token *token,
	t_final_token **final_token, t_final_token *new, char *content)
{
	while (token && token->type == CMD)
	{
		*final_token = handle_nodes(token, *final_token, new, content);
		token = token->next;
	}
	return (token);
}

t_clean_token	*manage_output_append(t_clean_token *token,
	t_final_token **final_token, t_final_token *new, char *content)
{
	while (token && (token->type == OUTPUT || token->type == APPEND))
	{
		if (!token->next || token->next->type == PIPE)
			*final_token = handle_nodes(token, *final_token, new, content);
		token = token->next;
	}
	return (token);
}

t_clean_token	*manage_pipes(t_clean_token *token,
	t_final_token **final_token, t_final_token *new, char *content)
{
	if (token && token->type == PIPE)
	{
		*final_token = handle_final_pipe(token, *final_token, new, content);
		token = token->next;
	}
	return (token);
}
