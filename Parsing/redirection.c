/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:08:38 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/29 16:43:17 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    test_redirection_input(t_clean_token *clean_node)
{
	int i = 0;
    while (clean_node && clean_node->next)
    {
        if ((clean_node->type == INPUT && clean_node->next->type == INPUT)
        || (clean_node->type == INPUT && clean_node->next->type == HERE_DOC))
        { 
		    if (redirection_input(clean_node) == 1)
				return ;
		}
        else if ((clean_node->type == OUTPUT && clean_node->next->type == OUTPUT)
        || (clean_node->type == OUTPUT && clean_node->next->type == APPEND))
            redirection_output(clean_node);
        else if ((clean_node->type == APPEND && clean_node->next->type == APPEND)
        || (clean_node->type == APPEND && clean_node->next->type == OUTPUT))
            redirection_append(clean_node);
		else if ((clean_node->type == HERE_DOC && clean_node->next->type == HERE_DOC)
		|| (clean_node->type == HERE_DOC && clean_node->next->type == INPUT))
		{
			redirection_here_doc(clean_node, i);
			i++;
		}
        clean_node = clean_node->next;

    }
}

void    read_here_doc(size_t i, char **limiter)
{
    char    *line;

    while (1)
    {
        line = get_next_line(0);
        if (ft_strncmp_limiter(line, limiter[i], ft_strlen(limiter[i])) == 0)
        {
            free(line);
			return ;
        }
        ft_putstr_fd(line, 1);
        free(line);
    }
}



void	redirection_here_doc(t_clean_token *clean_node, int i)
{
	char **limiter;

	limiter = ft_split(clean_node->content, ' ');
	read_here_doc(i, limiter);
}

int	redirection_input(t_clean_token *clean_node)
{
	int	filein;

	filein = 0;
	filein = open(clean_node->content, O_RDONLY, 0644);

	if (filein == -1)
	{
		// perror("Erreur file de sortie");
		// exit(EXIT_FAILURE);		
		printf("bash: %s No such file or directory\n", clean_node->content);
		return 1;	
	}
	close(filein);
	return 0;
}

// void	redirection_here_doc(t_clean_token *clean_node)
// {
// 	int	filein;

// 	filein = 0;
// 	filein = open(clean_node->content, O_RDONLY, 0644);

// 	if (filein == -1)
// 	{
// 		perror("Erreur file");
// 		exit(EXIT_FAILURE);
// 	}
// 	close(filein);
// }

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
