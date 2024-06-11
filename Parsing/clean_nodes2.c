/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_nodes2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 10:23:17 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/11 14:23:41 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_spaces_in_content(char *content)
{
	int	i;
	int	j;
	int	prev_space;

	if (content == NULL)
		return ;
	i = 0;
	j = 0;
	prev_space = 0;
	while (content[i] == ' ')
		i++;
	while (content[i] != '\0')
	{
		if (content[i] != ' ' || !prev_space)
		{
			content[j++] = content[i];
			prev_space = (content[i] == ' ');
		}
		i++;
	}
	content[j] = '\0';
}

void	clean_spaces1(t_token *token)
{
	while (token != NULL)
	{
		if (token->content != NULL)
		{
			clean_spaces_in_content(token->content);
		}
		token = token->next;
	}
}

int	clean_spaces2(t_token *token)
{
	int	i;

	while (token)
	{
		i = 0;
		if (token->content == NULL && token->type != PIPE)
		{
			printf("bash: syntax error\n");
			return (1);
		}
		if (token->type == INPUT || token->type == OUTPUT
			|| token->type == APPEND || token->type == HERE_DOC)
		{
			while (token->content[i] && token->content[i] != ' '
				&& token->content[i] != '\t')
				i++;
			token->content = ft_strndup(token->content, i);
		}
		token = token->next;
	}
	return (0);
}

int	clean_token_content(t_token *token)
{
	int	i;
	int	j;

	if (!token->content)
		return (0);
	i = 0;
	j = 0;
	while (token->content[i])
	{
		if (token->content[i] == '<' || token->content[i] == '>'
			|| token->content[i] == '|')
		{
			if (token->content[i + 1] == '\0'
				|| string_is_space(token->content + i + 1) == 1)
				return (1);
			i++;
		}
		else
			token->content[j++] = token->content[i++];
	}
	token->content[j] = '\0';
	return (0);
}

int	clean_chevron(t_token *token)
{
	while (token != NULL)
	{
		if (token->type == INPUT || token->type == OUTPUT
			|| token->type == APPEND || token->type == HERE_DOC)
		{
			if (clean_token_content(token))
				return (1);
		}
		token = token->next;
	}
	return (0);
}
