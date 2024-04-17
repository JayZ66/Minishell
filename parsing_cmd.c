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

void	clean_arg(t_token *token)
{
	int	i;
	int	j;
	while (token != NULL)
	{
		if (token->type == INPUT || token->type == OUTPUT || token->type == APPEND || token->type == HERE_DOC)
		{
			if (token->content)
			{
				i = 0;
				j = 0;
				while (token->content[i])
				{
					if (token->content[i] == '<' || token->content[i] == '>' || token->content[i] == '|')
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











