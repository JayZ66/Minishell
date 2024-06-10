/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:08:10 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/10 15:40:37 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_new_token(t_token *token, int i)
{
	t_token	*new;

	while (token->content[i] == ' ')
		i++;
	if (!token->content[i])
		return ;
	new = (t_token *)ft_malloc(sizeof(t_token));
	if (new == NULL)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	new->content = ft_strdup(token->content + i);
	ft_free(token->content);
	new->type = CMD;
	new->next = token->next;
	token->next = new;
}

void	cut_node(t_token *token)
{
	char	*temp;
	int		i;

	i = 0;
	while (token->content[i] && token->content[i] != ' ')
		i++;
	temp = ft_strndup(token->content, i);
	if (string_is_space(token->content + i) == 0)
	{
		create_new_token(token, i);
		token->content = temp;
	}
}

void	manage_node(t_token *token)
{
	while (token)
	{
		if (token->type == INPUT || token->type == OUTPUT
			|| token->type == APPEND || token->type == HERE_DOC)
			cut_node(token);
		token = token->next;
	}
}

int	verif_pipe(t_token *token)
{
	if (token->type == PIPE)
	{
		printf("bash syntax error: pipe\n");
		return (1);
	}
	while (token->next)
	{
		if (token->type == PIPE && token->next->type == PIPE)
		{
			printf("bash syntax error: pipe\n");
			return (1);
		}
		token = token->next;
	}
	return (0);
}
