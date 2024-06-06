/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:08:38 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/06 15:20:19 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirection_here_doc(t_clean_token *clean_node, int i)
{
	char	**limiter;

	limiter = ft_split(clean_node->content, ' ');
	read_here_doc(i, limiter);
	ft_free(limiter);
}

int	redirection_input(t_clean_token *clean_node)
{
	int	filein;

	filein = 0;
	filein = open(clean_node->content, O_RDONLY, 0644);
	if (filein == -1)
	{
		printf("bash: %s No such file or directory\n", clean_node->content);
		return (1);
	}
	close(filein);
	return (0);
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
