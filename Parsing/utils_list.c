/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:04:26 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/03 17:39:45 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int	string_is_space(char *token)
{
	if (token == NULL)
		return (1);
	while (token)
	{
		if (*token != ' ' && *token != '\t')
			return (0);
		token++;
	}
	return (1);
}

void	free_that_final_lst(t_final_token *token)
{
    t_final_token *temp;

    while (token)
    {
        temp = token;
        token = token->next;
        free(temp->content);
        free(temp);
	}
}

void	check_directory(t_token	*node)
{
	while (node)
	{
		if (node->type == CMD && only_slash(node->content) == 1)
			printf("bash: %s: Is a directory\n", node->content);
		node = node->next;
	}
}

int	only_slash(char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		if (content[i] == '/' || content[i] == '.')
			i++;
		else
			return (0);
	}
	return (1);
}
