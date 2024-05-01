/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_line_for_pipex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 15:39:46 by marvin            #+#    #+#             */
/*   Updated: 2024/03/25 15:39:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**lst_to_tab(t_token *token)
{
	char	**pipex_cmd_line;
	t_token	*temp;
	int		size_lst;
	size_t	i;

	size_lst = lst_size(token);
	i = 0;
	pipex_cmd_line = (char **)malloc(sizeof(char *) * (size_lst + 1));
	if (!pipex_cmd_line)
	{
		perror("Can't create new cmd line\n");
		exit(EXIT_FAILURE);
	}
	while (token != NULL)
	{
		temp = token->next;
		pipex_cmd_line[i] = ft_strdup(token->content);
		if (pipex_cmd_line[i] == NULL)
		{
			perror("Can't copy content from list\n");
			while (pipex_cmd_line[i] != NULL)
				free(pipex_cmd_line[++i]);
			free(pipex_cmd_line);
			exit(EXIT_FAILURE);
		}
		i++;
		free(token->content);
		token = temp;
	}
	free(token); // Check if we need token = NULL;
	pipex_cmd_line[size_lst] = NULL;
	// print_tab(pipex_cmd_line);
	return (pipex_cmd_line);
}

/*
Lorsque nous utilisons malloc(sizeof(char *) * (count + 1)),
cela alloue de la mémoire pour count + 1 pointeurs de caractères
(char *). Le +1 est ajouté spécifiquement pour permettre la place
pour le pointeur NULL de terminaison à la fin du tableau de tableaux.

Ainsi, lors de l'attribution de la valeur NULL à argv[count],
nous indiquons simplement que la dernière entrée du tableau de
tableaux est NULL, sans avoir besoin d'ajouter 1 à la valeur de count.
En effet, count contient déjà le nombre d'éléments dans le tableau,
donc argv[count] pointe au-delà de la dernière entrée valide, où nous
plaçons le NULL de terminaison.
*/


// 1. Déterminer la longueur totale de la chaîne résultante.
// char	*list_to_string(t_token *token)
// {
// 	size_t	str_size;
// 	size_t	index;
// 	char	*line_cmd;
// 	t_token	*temp;

// 	str_size = ft_lstsize_content(token);
// 	printf("Size lst content : %ld\n", str_size);
// 	index = 0;
// 	print_lst(token);
// 	line_cmd = (char *)malloc(sizeof(char) * (str_size + 1));
// 	if (!line_cmd)
// 	{
// 		perror("Can't get the line cmd from list\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	temp = token;
// 	while (temp)
// 	{
// 		ft_strcat(line_cmd, temp->content, ft_strlen(temp->content));
// 		// printf("each line : %s\n", line_cmd);
// 		index += ft_strlen(temp->content);
// 		temp = temp->next;
// 	}
// 	line_cmd[index] = '\0';
// 	return (line_cmd);
// }

// char	*check_line_cmd(t_token *token)
// {
// 	char	*line_cmd;
// 	// int		i;

// 	line_cmd = list_to_string(token);
// 	printf("Ligne de cmd : %s\n", line_cmd);
// 	return (printf("OK"), "OK");
// }

/*
STEPS :
1. I need to convert my cmd line from nodes to one string.
2. Then i'll (after) check all errors to modify this string for pipex.
3. I'll convert this string with a split.
*/
