/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:35:13 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/10 18:12:05 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input_redirection(t_clean_token *clean_node)
{
	if ((clean_node->type == INPUT && clean_node->next->type == INPUT)
		|| (clean_node->type == INPUT && clean_node->next->type == HERE_DOC))
	{
		if (redirection_input(clean_node) == 1)
			return (1);
	}
	return (0);
}

void	handle_output_redirection(t_clean_token *clean_node)
{
	if ((clean_node->type == OUTPUT && clean_node->next->type == OUTPUT)
		|| (clean_node->type == OUTPUT && clean_node->next->type == APPEND))
	{
		redirection_output(clean_node);
	}
}

void	handle_append_redirection(t_clean_token *clean_node)
{
	if ((clean_node->type == APPEND && clean_node->next->type == APPEND)
		|| (clean_node->type == APPEND && clean_node->next->type == OUTPUT))
	{
		redirection_append(clean_node);
	}
}

void	handle_here_doc_redirection(t_clean_token *clean_node, int i)
{
	if ((clean_node->type == HERE_DOC && clean_node->next->type == HERE_DOC)
		|| (clean_node->type == HERE_DOC && clean_node->next->type == INPUT))
	{
		redirection_here_doc(clean_node, i);
	}
}

int	test_redirection_input(t_clean_token *clean_node)
{
	int	i;

	i = 0;
	while (clean_node && clean_node->next)
	{
		if (handle_input_redirection(clean_node))
			return (1);
		handle_output_redirection(clean_node);
		handle_append_redirection(clean_node);
		handle_here_doc_redirection(clean_node, i);
		clean_node = clean_node->next;
	}
	return (0);
}
