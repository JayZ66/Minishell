/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:02:21 by romlambe          #+#    #+#             */
/*   Updated: 2024/04/03 14:30:01 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*clean_arg(t_token **token)
// {
// 	int	i;
// 	char	*cmd;
// 	t_token	*new;
// 	t_token	*temp;
// 	t_token *result;

// 	new = NULL;
// 	temp = *token;
// 	result = NULL;
// 	while (temp != NULL)
// 	{
// 		i = 0;
// 		while (temp->content[i] == ' ')
// 			i++;
// 		if (temp->type == ARG)
// 		{
// 			cmd = ft_strdup((*token)->content);
// 			printf("commande complète: %s\n", cmd);
// 			new = init_node(cmd, ARG);
// 			add_back(&result, new);
// 		}
// 		temp = temp->next;
// 	}
// 	return (result);
// }

t_clean_token	*clean_arg(t_token **token)
{
	t_clean_token	*new;
	t_clean_token	*clean_token;
	// char			*arg;
	// char			*temp;
	new = NULL;
	clean_token = NULL;
	while(*token)
	{
		if ((*token)->type == ARG)
		{
			if (clean_token == NULL)
			{
				// arg = ft_strdup((*token)->content);
				clean_token = init_clean_node((*token)->content);
				// add_clean_back(clean_token, new);
				new = clean_token;
			}
			else
			{
				// temp = ft_strjoin(arg, " ");
				// free(arg);
				// arg = ft_strjoin(temp, (*token)->content);
				// free(temp);
				new->next = init_clean_node((*token)->content);
				new = new->next;
			}
		}
		*token = (*token)->next;
	}
	return (clean_token);
}
