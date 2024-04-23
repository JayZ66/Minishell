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


// t_token	*clean_arg(t_token **token)
// {
// 	t_token	*clean_token = NULL;
// 	t_token	*new = NULL;
// 	char	*arg = NULL;

// 	while (*token)
// 	{
// 		if ((*token)->type == ARG && (*token)->next->type == INPUT)
// 		{
// 			arg = ft_strdup((*token)->content);
// 			clean_token = init_node(arg, INPUT);
// 			add_back(&new, clean_token);
// 			(*token) = (*token)->next;
// 		}
// 		else
// 		{
// 			if (arg == NULL)
// 				arg = ft_strdup((*token)->content);
// 			else
// 			{
// 				char *temp = ft_strjoin(arg, " ");
// 				free(arg);
// 				arg = ft_strjoin(temp, (*token)->content);
// 				free(temp);
// 			}
// 		}
// 		(*token) = (*token)->next;
// 	}
// 	return (new);
// }

// t_clean_token	*clean_arg(t_token **token)
// {
// 	t_clean_token	*clean_token = NULL;
// 	t_clean_token	*new = NULL;
// 	char			*arg = NULL;

// 	while (*token)
// 	{
// 		if ((*token)->type == ARG)
// 		{
// 			if (arg == NULL)
// 				arg = ft_strdup((*token)->content);
// 			else
// 			{
// 				char *temp = ft_strjoin(arg, " ");
// 				free(arg);
// 				arg = ft_strjoin(temp, (*token)->content);
// 				free(temp);
// 			}
// 		}
// 		else if (arg != NULL)
// 		{
// 			if (clean_token == NULL)
// 			{
// 				clean_token = init_clean_node(arg);
// 				new = clean_token;
// 			}
// 			else
// 			{
// 				new->next = init_clean_node(arg);
// 				new = new->next;
// 			}
// 			free(arg);
// 			arg = NULL;
// 		}
// 		*token = (*token)->next;
// 	}

// 	if (arg != NULL)
// 	{
// 		if (clean_token == NULL)
// 			clean_token = init_clean_node(arg);
// 		else
// 			new->next = init_clean_node(arg);
// 		free(arg);
// 	}

// 	return (clean_token);
// }

// t_clean_token	*clean_arg(t_token **token)
// {
// 	t_clean_token	*clean_token = NULL;
// 	t_clean_token	*new = NULL;
// 	char			*arg = NULL;
// 	char			*temp = NULL;
// 	while(*token)
// 	{
// 		if((*token)->type == ARG && (*token)->next->type == INPUT)
// 		{
// 			if (arg == NULL)
// 			{
// 				arg = ft_strdup((*token)->content);

// 				*token = (*token)->next;
// 			}
// 			else
// 				temp = ft_strjoin(arg, " ");
// 				free(arg);
// 				arg = ft_strjoin(temp, (*token)->content);
// 				free(temp);

// 		}
// 		else if ((*token)->type == INPUT && (*token)->next->type == ARG)
// 		{

// 		}
// 	}
// }


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

// t_clean_token	*copy_list(t_token *token, t_clean_token **clean_token)
// {
// 	t_clean_token	*new_node;
// 	t_clean_token	*last_node;

// 	while (token)
// 	{
// 		new_node = (t_clean_token *)malloc(sizeof(t_clean_token));
// 		if (!new_node)
// 		{
// 			perror("Erreur de mémoire");
// 			exit(EXIT_FAILURE);
// 		}
// 		if (token->type != PIPE)
// 			new_node->content = ft_strdup(token->content);
// 		new_node->type = token->type;

// 		new_node->next = NULL;
// 		last_node = NULL;
// 		new_node->prev = last_node;

// 		if ((!*clean_token))
// 			*clean_token = new_node;
// 		else
// 			last_node = *clean_token;
// 		// while (!last_node)
// 		// 	last_node = last_node->next;

// 		last_node = new_node;
// 		token = token->next;
// 	}
// 	return (*clean_token);
// }

// t_token *clean_arg(t_token **token)
// {
// 	t_token *clean_token = NULL;
// 	t_token *new = NULL;
// 	char *arg = NULL;

// 	while (*token)
// 	{
// 		if ((*token)->type == ARG)
// 		{
// 			arg = ft_strdup((*token)->content);
// 			if ((*token)->next && (*token)->next->type == INPUT)
// 			{
//                 clean_token = init_node(arg, INPUT);
//                 add_back(&new, clean_token);
//                 (*token) = (*token)->next;
//             }
//             else
//             {
//                 // Traitement pour d'autres types de nodes si nécessaire
// 				clean_token = init_node(arg, ARG);
//                 add_back(&new, clean_token);
//             }
//             free(arg); // Libérer la mémoire après utilisation
//         }
// 		else if ((*token)-> type == INPUT)
// 		{
// 			if((*token)->next && (*token)->next->type == ARG)
// 			{
// 				arg = ft_strdup((*token)->next->content);
// 				clean_token = init_node(arg, INPUT);
// 				add_back(&new, clean_token);
// 				free(arg);
// 				(*token) = (*token)->next;
// 			}
// 		}
//         // else
//         // {
//         //     // Gestion des autres types de nodes
//         //     clean_token = init_node(ft_strdup((*token)->content), PIPE);
//         //     add_back(&new, clean_token);
//         // }
//         (*token) = (*token)->next;
//     }
//     return (new);
// }


// t_clean_token	*copy_lst(t_token *token)
// {
// 	t_clean_token	*clean_token = NULL;
// 	t_clean_token	*new = NULL;
// 	char			*content = NULL;

// 	while (token)
// 	{
// 		if (token->type != PIPE)
// 			content = ft_strdup(token->content);
// 		else
// 			content = NULL;
// 		clean_token = init_clean_node(content, token->type);
// 		add_clean_back(&new, clean_token);
// 		free(content);
// 		token = token->next;
// 	}
// 	return (new);
// }

t_clean_token *copy_lst(t_token *token)
{
    t_clean_token *clean_token = NULL;
    t_clean_token *new = NULL; // Initialisez new à NULL
    t_clean_token *last_node = NULL;

    while (token)
    {
        char *content = NULL;
        if (token->type != PIPE)
            content = ft_strdup(token->content);

        t_clean_token *clean_node = init_clean_node(content, token->type);

        if (!clean_token) {
            clean_token = clean_node;
            new = clean_token; // Mettez à jour new pour pointer vers le premier nœud
        } else {
            last_node->next = clean_node; // Connectez le nouveau nœud après le dernier nœud trouvé
            clean_node->prev = last_node; // Mettez à jour les liens vers le nœud précédent
        }

        last_node = clean_node; // Mettez à jour last_node pour pointer vers le dernier nœud ajouté
        token = token->next;
    }
    return new;
}




t_clean_token	*redirection_node(t_token **token)
{
	t_clean_token *clean_node;
}












