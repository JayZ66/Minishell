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
	// if (!token->content[i] || string_is_space(token->content + i, i) == 0)
	// 	{
	// 		perror("Manque le file après le couz");
	// 		exit(EXIT_FAILURE);
	// 	}
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

// t_clean_token *copy_lst(t_token *token)
// {
//     t_clean_token *clean_token = NULL;
//     t_clean_token *new = NULL; // Initialisez new à NULL
//     t_clean_token *last_node = NULL;
// 	t_clean_token *clean_node;
//     while (token)
//     {
//         char *content = NULL;
//         if (token->type != PIPE)
// 		{
// 			content = ft_strdup(token->content);
// 			clean_node = init_clean_node(content, token->type);
// 		}
// 		else
// 		{
// 			content = ft_strdup("|");
// 			clean_node = init_clean_node(content, token->type); //creer une ft init node pour le pipe
// 		}
//         if (!clean_token) {
//             clean_token = clean_node;
//             new = clean_token; // Mettez à jour new pour pointer vers le premier nœud
//         } else {
//             last_node->next = clean_node; // Connectez le nouveau nœud après le dernier nœud trouvé
//             clean_node->prev = last_node; // Mettez à jour les liens vers le nœud précédent
//         }

//         last_node = clean_node; // Mettez à jour last_node pour pointer vers le dernier nœud ajouté
//         token = token->next;
// 		if (clean_node->prev)
// 			printf("previous = %s\n", clean_node->prev->content);
// 		else
// 			printf("previous is NULL\n");
// 	}
//     return new;
// }


// void	redirection_node(t_clean_token **head_ref)
// {
//     t_clean_token *current = *head_ref;

//     while (current && current->next)
//     {
//         if (current->type == ARG && current->next->type == INPUT)
//         {
//             // Récupérer le nœud de type ARG et son précédent
//             t_clean_token *arg_node = current->next;
//             t_clean_token *prev_arg_node = arg_node->prev;
// 			// printf("previous = %s\n", current->prev->content);
//             // Déplacer le nœud de type ARG avant le nœud de type INPUT
// 			printf("prev arg: %s\n", prev_arg_node->content);
//             if (prev_arg_node)
//             {
//                 prev_arg_node->next = arg_node->next;
//                 if (arg_node->next)
//                     arg_node->next->prev = prev_arg_node;
//                 arg_node->next = current;
//                 arg_node->prev = current->prev;
//                 current->prev = arg_node;
//                 *head_ref = arg_node;
//             }
//         }
//         current = current->next;
//     }
// }


//A VOIR SI JE L'UTILISE VRAIMENT OU PAS (je reflechis si j'ai besoin de swap ou si juste j'avance sur ma ligne
//je me comprends)

// void redirection_node(t_clean_token **head_ref)
// {
//     t_clean_token *current = *head_ref;

//     while (current && current->next)
//     {
//         if (current->type == ARG && current->next->type == INPUT)
//         {
//             // Récupérer le nœud de type ARG et son précédent
//             t_clean_token *arg_node = current;
//             t_clean_token *input_node = current->next;
//             t_clean_token *prev_arg_node = arg_node->prev;

//             // Vérifier que le nœud de type ARG est bien précédé par un nœud de type INPUT
//             if (prev_arg_node && prev_arg_node->type == INPUT)
//             {
//                 // Mettre à jour les pointeurs next et prev pour le nœud précédant le nœud de type ARG
//                 prev_arg_node->next = input_node;

//                 // Mettre à jour les pointeurs next et prev pour le nœud suivant le nœud de type INPUT
//                 if (input_node->next)
//                     input_node->next->prev = arg_node;

//                 // Mettre à jour les pointeurs next et prev pour le nœud de type ARG
//                 arg_node->prev = input_node;
//                 arg_node->next = input_node->next;

//                 // Mettre à jour les pointeurs next et prev pour le nœud de type INPUT
//                 input_node->prev = prev_arg_node;
//                 input_node->next = arg_node;

//                 // Mettre à jour la tête de la liste si nécessaire
//                 if (*head_ref == arg_node)
//                     *head_ref = input_node;
//             }
//         }
//         current = current->next;
//     }
// }

// void	test_redirection_input(t_clean_token *clean_node)
// {
// 	while (clean_node && clean_node->type != PIPE)
// 	{
// 		if (clean_node->type == INPUT && clean_node->next->type == INPUT)
// 		{
// 			while (clean_node->type == INPUT)
// 			{
// 				redirection_input(clean_node);
// 				clean_node = clean_node->next;
// 			}
// 		}
// 		else if (clean_node->type == INPUT)
// 		{
// 			redirection_last_input(clean_node);
// 			clean_node = clean_node->next;
// 		}
// 		else
// 			clean_node = clean_node->next;
// 	}
// }

// void	redirection_last_input(t_clean_token *clean_node)
// {
// 	int	filein;
// 	int	fd[2];

// 	filein = open(clean_node->content, O_RDONLY, 0777);
// 	if (filein == -1)
// 	{
// 		perror("Erreur dernier file");
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fd[1], STDOUT_FILENO);
// 	dup2(filein, STDIN_FILENO);
// }

// void	redirection_input(t_clean_token *clean_node)
// {
// 	int	filein;
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 		exit(EXIT_FAILURE);
// 	filein = open(clean_node->content, O_RDONLY, 0777);
// 	printf("%i\n", filein);
// 	printf("%s\n", clean_node->content);
// 	if (filein == -1)
// 	{
// 		perror("Erreur file");
// 		exit(EXIT_FAILURE);
// 	}
// 	dup2(fd[1], STDOUT_FILENO);
// 	dup2(filein, STDIN_FILENO);
// 	close(fd[0]);
// }

int	input_in_bloc(t_token *token, int i)
{
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == INPUT)
			i++;
		token = token->next;
	}
	return (i);
}

// t_clean_token	*copy_lst(t_token *token, t_clean_token *clean_list)
// {
// 	int				i;
// 	t_token			*head;
// 	char			*content;
// 	t_clean_token	*new;

// 	i = 0;
// 	content = NULL;
// 	new = NULL;
// 	head = (token);
// 	if (input_in_bloc(token, i) > 0)
// 	{
// 		while(token)
// 		{
// 			if ((token)->type == INPUT)
// 			{
// 				content = ft_strdup((token)->content);
// 				new = init_clean_node(content, (token)->type);
// 				add_clean_back(&clean_list, new);
// 				free (content);
// 				i--;
// 			}
// 			(token) = (token)->next;
// 		}
// 		(token) = head;
// 		while ((token) || (token)->type == PIPE)
// 		{
// 			if ((token)->type == ARG)
// 			{
// 				content = ft_strdup((token)->content);
// 				new = init_clean_node(content, (token)->type);
// 				add_clean_back(&clean_list, new);
// 				free (content);
// 			}
// 			(token) = (token)->next;
// 		}
// 		(token) = head;
// 		while ((token) || ((token)->type == OUTPUT))
// 		{
// 			if ((token)->type  == OUTPUT)
// 			{
// 				content = ft_strdup((token)->content);
// 				new = init_clean_node(content, (token)->type);
// 				add_clean_back(&clean_list, new);
// 				free (content);
// 			}
// 			(token) = (token)->next;
// 		}
// 	}
// 	return (clean_list);
// }


//faire que le input fonctionne apres un pipe
//gerer le append
// split la commande

// faire une fonction pour ouvrir et close les input et juste ouvrir le dernier
// faire une fonction pareil pour les outputs + les creer s'ils existent pas
// j'ai pas fait dpeuis pipex jsp si j'vais y arriver zebi
t_clean_token	*copy_lst(t_token *token, t_clean_token **clean_list)
{
	int				i;
	t_token			*head;
	t_clean_token	*new;
	char			*content;

	i = 0;
	head = token;
	// new = NULL;
	content = NULL;
	// clean_list = NULL;
	if (input_in_bloc(token, i) > 0)
	{
		while (i >= 0)
		{
			if (token->type == INPUT)
			{
				content = ft_strdup(token->content);
				new = init_clean_node(content, token->type);
				add_clean_back(clean_list, new);
				free (content);
				i--;
			}
			token = token->next;
		}
		token = head;
		while (token)
		{
			if ((token)->type == ARG)
			{
				content = ft_strdup((token)->content);
				new = init_clean_node(content, (token)->type);
				add_clean_back(clean_list, new);
				free (content);
			}
			(token) = (token)->next;
		}
		token = head;
		while (token)
		{
			if ((token)->type == OUTPUT)
			{
				content = ft_strdup((token)->content);
				new = init_clean_node(content, (token)->type);
				add_clean_back(clean_list, new);
				free (content);
			}
			(token) = (token)->next;
		}
	}
	return (*clean_list);
}

// t_clean_token *copy_lst(t_token *token, t_clean_token **clean_list)
// {
//     // t_token *head = token; // Sauvegarde de la tête de la liste d'origine

//     while (token != NULL)
//     {
//         // Traitement des tokens et ajout à la liste clean_list
//         if (token->type == INPUT || token->type == ARG || token->type == OUTPUT)
//         {
//             char *content = ft_strdup(token->content);
//             t_clean_token *new = init_clean_node(content, token->type);
//             add_clean_back(clean_list, new);
//             free(content); // Libération de la mémoire allouée dynamiquement
//         }
//         token = token->next;
//     }

//     return *clean_list;
// }

