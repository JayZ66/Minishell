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

// TO DO : Function that free the entire list !


t_token    *init_node(char *content, Token_type type)
{
    t_token    *token;

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
    token->type = type;
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

int	lst_size(t_token *token)
{
	size_t	count;

	count = 0;
	if (!token)
	{
		perror("List is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token) // No token->next bce we've to go at the end of the lst.
	{
		token = token->next;
		count++;
	}
	return (count);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	manage_file(int nb_args, char **cmd_line, int flag)
{
	int	first_file;
	int	last_file;

	first_file = 0;
	last_file = 0;
	if (flag == 2)
		last_file = open(cmd_line[nb_args - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (flag == 1)
		last_file = open(cmd_line[nb_args - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (flag == 0)
		first_file = open(cmd_line[0], O_RDONLY, 0644);
	if (last_file == -1 || first_file == -1)
		return (perror("Can't open file\n"), exit(EXIT_FAILURE), 1);
	else if (last_file)
		return (last_file);
	else if (first_file)
		return (first_file);
	return (1);
}

int	ft_strlen_tab(char **cmd_line)
{
	size_t	i;

	i = 0;
	while (cmd_line[i])
		i++;
	return (i);
}

int	ft_lstsize_content(t_token *token)
{
	size_t	total_length;
	t_token	*temp;

	total_length = 0;
	temp = token;
	while (temp != NULL)
	{
		total_length += ft_strlen(token->content);
		temp = temp->next;
	}
	return (total_length);
}

char	*ft_strcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	printf("Line previous cat dst : %s\n", dst);
	printf("Line previous cat src : %s\n", src);
	if (size <= 0)
		return (perror("Can't concatenate\n"), NULL);
	while (dst[i]) // Check if we need a strcopy at first ?
		i++;
	while (src[j] && j < size)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	printf("Line cat : %s\n", dst);
	return (dst);
}

void	print_lst(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("Chaque node content : %s\n", tmp->content);
		printf("Chaque node type content : %u\n", tmp->type);
		tmp = tmp->next;
	}
}
