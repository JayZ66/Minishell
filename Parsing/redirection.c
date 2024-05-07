/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:08:38 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/07 14:00:58 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	test_redirection_input(t_clean_token *clean_node)
{
	while (clean_node && clean_node->next)
	{
		if (clean_node->type == INPUT && clean_node->next->type == INPUT)
			redirection_input(clean_node);
		else if (clean_node->type == OUTPUT && clean_node->next->type == OUTPUT)
			redirection_output(clean_node);
		else if (clean_node->type == APPEND && clean_node->next->type == APPEND) // BUT CAN BE ALSO APPEND & OUTPUT or else.
			redirection_append(clean_node);
		clean_node = clean_node->next;
	}
}

void	redirection_input(t_clean_token *clean_node)
{
	int	filein;

	filein = 0;
	filein = open(clean_node->content, O_RDONLY, 0644);

	if (filein == -1)
	{
		perror("Erreur file");
		exit(EXIT_FAILURE);
	}
	close(filein);
}

void	redirection_output(t_clean_token *clean_node)
{
	int	fileout;

	fileout = 0;
	fileout = open(clean_node->content, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fileout == -1)
	{
		perror("Erreur file de sortie");
		exit(EXIT_FAILURE);
	}
	close(fileout);
}

void	redirection_append(t_clean_token *clean_node)
{
	int	fileout;

	fileout = 0;
	fileout = open(clean_node->content, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fileout == -1)
	{
		perror("Erreur file de sortie");
		exit(EXIT_FAILURE);
	}
	close(fileout);
}


int	input_in_bloc(t_clean_token *token, int i)
{
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == INPUT)
			i++;
		token = token->next;
	}
	return (i);
}
