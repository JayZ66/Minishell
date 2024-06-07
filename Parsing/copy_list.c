/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:09:29 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 11:21:56 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_clean_token	*handle_inputs(t_token **token)
{
	char			*content;
	t_clean_token	*clean_list;
	t_clean_token	*new;

	clean_list = NULL;
	while (*token != NULL && (*token)->type != PIPE)
	{
		if ((*token)->type == INPUT || (*token)->type == HERE_DOC)
		{
			if (!*token || string_is_space((*token)->content) == 1)
			{
				printf("syntax error \n");
				return (NULL);
			}
			content = (*token)->content;
			new = init_clean_node(content, (*token)->type);
			add_clean_back(&clean_list, new);
		}
		*token = (*token)->next;
	}
	return (clean_list);
}

t_clean_token	*handle_commands(t_token **token)
{
	char			*content;
	t_clean_token	*clean_list;
	t_clean_token	*new;

	clean_list = NULL;
	while (*token != NULL && (*token)->type != PIPE)
	{
		if ((*token)->type == CMD)
		{
			if (ft_strncmp((*token)->content, "&&", 2) == 0)
			{
				printf("syntax error &&\n");
				return (NULL);
			}
			content = (*token)->content;
			new = init_clean_node(content, (*token)->type);
			add_clean_back(&clean_list, new);
		}
		*token = (*token)->next;
	}
	return (clean_list);
}

t_clean_token	*handle_outputs(t_token **token)
{
	char			*content;
	t_clean_token	*clean_list;
	t_clean_token	*new;

	clean_list = NULL;
	while (*token != NULL && (*token)->type != PIPE)
	{
		if ((*token)->type == OUTPUT || (*token)->type == APPEND)
		{
			if (!*token || string_is_space((*token)->content) == 1)
			{
				printf("syntax error \n");
				return (NULL);
			}
			content = (*token)->content;
			new = init_clean_node(content, (*token)->type);
			add_clean_back(&clean_list, new);
		}
		*token = (*token)->next;
	}
	return (clean_list);
}

void	handle_pipe(t_token **token, t_clean_token **clean_list)
{
	char			*content;
	t_clean_token	*new;

	if (*token != NULL && (*token)->type == PIPE)
	{
		content = ft_strdup("|");
		new = init_clean_node(content, (*token)->type);
		add_clean_back(clean_list, new);
		*token = (*token)->next;
	}
}

t_clean_token	*copy_lst(t_token *token)
{
	t_clean_token	*clean_list;
	t_clean_token	*temp_list;
	t_token			*block_start;

	clean_list = NULL;
	while (token != NULL)
	{
		block_start = token;
		temp_list = handle_inputs(&token);
		add_clean_back(&clean_list, temp_list);
		token = block_start;
		temp_list = handle_commands(&token);
		add_clean_back(&clean_list, temp_list);
		token = block_start;
		temp_list = handle_outputs(&token);
		add_clean_back(&clean_list, temp_list);
		handle_pipe(&token, &clean_list);
	}
	return (clean_list);
}
