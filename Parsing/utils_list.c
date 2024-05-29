/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 17:04:26 by romlambe          #+#    #+#             */
/*   Updated: 2024/05/29 16:33:19 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_token	*lst_last(t_token *token)
// {
// 	if (token == NULL)
// 	{
// 		perror("Token node is empty\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (token->next)
// 		token = token->next;
// 	return (token);
// }

// void	add_back(t_token **token, t_token *new)
// {
// 	t_token	*last;

// 	if (!token)
// 	{
// 		perror("List is empty\n");
// 		EXIT_FAILURE;
// 	}
// 	if (!(*token)) // To check !
// 		*token = new;
// 	else
// 	{
// 		last = lst_last(*token);
// 		last->next = new;
// 	}
// }

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

char	**realloc_env(char **env)
{
	char	**new_env;
	size_t	size_env;
	size_t	i;

    // Calculer la taille de l'environnement
    for (size_env = 0; env[size_env]; size_env++)
        ;
    // Allouer la mémoire pour le nouvel environnement
    new_env = (char **)malloc(sizeof(char *) * (size_env + 1));
    if (!new_env)
    {
        perror("Can't create the new env.\n");
        exit(EXIT_FAILURE);
    }
    // Copier les chaînes de caractères
    for (i = 0; i < size_env; i++)
    {
        new_env[i] = strdup(env[i]);
        if (!new_env[i])
        {
            perror("Can't duplicate env string.\n");
            // Libérer les chaînes déjà dupliquées et l'environnement
            while (i > 0)
            {
                free(new_env[--i]);
            }
            free(new_env);
            exit(EXIT_FAILURE);
        }
    }
    new_env[size_env] = NULL;
    return (new_env);
}

void    free_that_final_lst(t_final_token **token)
{
	t_final_token	*tmp;

	// if (!(*token))
	// {
	// 	perror("Clean lst is empty, can't free\n");
	// 	exit(EXIT_FAILURE);
	// }
	while(*token)
	{
		tmp = (*token)->next;
		free((*token)->content);
		free(*token);
		*token = tmp;
	}
	*token = NULL;
}

//gerer l'espace si par exemple "/// | //././"
// finir correctement la ft pour "/...   -> ca n'existe pas"
void	check_directory(t_token	*node)
{
	while(node)
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
