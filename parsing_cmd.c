/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:02:21 by romlambe          #+#    #+#             */
/*   Updated: 2024/04/10 14:50:58 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_spaces(t_token *token)
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
		printf("token->content clean space %s\n", token->content);
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
		new->type = ARG;
		new->next = token->next;
		token->next = new;
		free(token->content);
		token->content = ft_strdup(temp);
		free(temp);
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

//devoir gerer les cas d'erreurs si on a par exemple
// <file cmd <file cmd
// avoir qu'une cmd par bloc si plus erreur
void	test_redirection_input(t_clean_token *clean_node)
{
	while (clean_node && clean_node->next)
	{
		if (clean_node->type == INPUT && clean_node->next->type == INPUT)
			redirection_input(clean_node);
		else if (clean_node->type == OUTPUT && clean_node->next->type == OUTPUT)
			redirection_output(clean_node);
		else if (clean_node->type == APPEND && clean_node->next->type == APPEND)
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

//gerer le append
// split la commande

// faire une fonction pour ouvrir et close les input et juste ouvrir le dernier
// faire une fonction pareil pour les outputs + les creer s'ils existent pas
// j'ai pas fait dpeuis pipex jsp si j'vais y arriver zebi


t_clean_token *copy_lst(t_token *token)
{
    // t_token *head = token;
    t_clean_token *clean_list = NULL;
    char *content = NULL;

    while (token != NULL)
    {
        t_token *block_start = token; // Pointeur de départ pour le bloc actuel

        while (token != NULL && token->type != PIPE)
        {
            if (token->type == INPUT || token->type == HERE_DOC)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Ajouter les arguments pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == ARG)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Ajouter les sorties pour ce bloc
        token = block_start;
        while (token != NULL && token->type != PIPE)
        {
            if (token->type == OUTPUT || token->type == APPEND)
            {
                content = ft_strdup(token->content);
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
            }
            token = token->next;
        }

        // Passer au prochain bloc s'il y en a un
        if (token!= NULL)
        {
			if (token->type == PIPE)
			{
				content = ft_strdup("|");
                t_clean_token *new = init_clean_node(content, token->type);
                add_clean_back(&clean_list, new);
                free(content);
			}
            token = token->next; // Avancer pour sauter le pipe
        }
    }
    return clean_list;
}



