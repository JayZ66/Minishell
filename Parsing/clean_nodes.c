/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:08:10 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/15 15:38:34 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clean_spaces1(t_token *token)
{
	int	i;
	int	j;
	int prev_space;
	while (token != NULL)
	{
		if (token->content != NULL)
		{
			i = 0;
			j = 0;
			prev_space = 0;
			while (token->content[i] == ' ')
				i++;
			while (token->content[i] != '\0')
			{
				if (token->content[i] != ' ' || !prev_space)
				{
					token->content[j++] = token->content[i];
					prev_space = (token->content[i] == ' ');
				}
				i++;
			}
			token->content[j] = '\0';
		}
		token = token->next;
	}
}

void	clean_spaces2(t_token *token)
{
	int	i;

	// i = 0;
	while (token)
	{
		i = 0;
		if (token->type == INPUT || token->type == OUTPUT || token->type == APPEND
			|| token->type == HERE_DOC)
		{
			while (token->content[i] && token->content[i] != ' '
				&& token->content[i] != '\t')
				i++;
			token->content = ft_strndup(token->content, i);
		}
		// printf("token->content clean space %s\n", token->content);
		token = token->next;
	}

}

void	clean_chevron(t_token *token)
{
	int	i;
	int	j;
	while (token != NULL)
	{
		if (token->type == INPUT || token->type == OUTPUT
			|| token->type == APPEND|| token->type == HERE_DOC)
		{
			if (token->content)
			{
				i = 0;
				j = 0;
				while (token->content[i])
				{
					if (token->content[i] == '<' || token->content[i] == '>'
						|| token->content[i] == '|')
						i++;
					else
						token->content[j++] = token->content[i++];
				}
				token->content[j] = '\0';
			}
		}
		token = token->next;
	}
}

void	cut_node(t_token *token)
{
	char	*temp;
	t_token	*new;
	int		i;

	i = 0;
	while (token->content[i] && token->content[i] != ' ')
		i++;
	temp = ft_strndup(token->content, i);
	if (string_is_space(token->content + i) == 0)
	{
		while (token->content[i] == ' ')
			i++;
		if (!token->content[i])
			return ;
		new = (t_token *)malloc(sizeof(t_token));
		if (new == NULL)
		{
			perror("Erreur d'allocation de mémoire");
			exit(EXIT_FAILURE);
		}
		new->content = ft_strdup(token->content + i);
		new->type = CMD;
		new->next = token->next;
		token->next = new;
		free(token->content);
		token->content = ft_strdup(temp);
		free(temp);
	}
}

void	manage_node(t_token *token)
{
	while(token)
	{
		if (token->type == INPUT)
			cut_node(token);
		if (token->type == OUTPUT)
			cut_node(token);
		if (token->type == APPEND)
			cut_node(token);
		if (token->type == HERE_DOC)
			cut_node(token);
		token = token->next;
	}
}

int		verif_pipe(t_token *token)
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
