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

#include "minishell.h"

t_token	*init_node(char *content)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (token == NULL)
	{
		perror("List has not been created\n");
		exit(EXIT_FAILURE);
	}
	token->content = ft_strdup(content); // Add token function here !
	if (token->content == NULL)
	{
		perror("Memory allocation failde\n");
		exit(EXIT_FAILURE);
	}
	token->next = NULL;
	return (token);
}

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
		EXIT_FAILURE;
	}
	if (!(*token)) // To check !
		*token = new;
	else
	{
		last = lst_last(*token);
		last->next = new;
	}	
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dest;
	size_t	i;

	if (s == NULL || n == 0)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (n + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		dest[i] = s[i];
		if (dest[i] == '\n')
			dest[i] = '\0';
		i++;
	}
	dest[i] = '\0';
	printf("Ma string : %s\n", dest);
	return (dest);
}