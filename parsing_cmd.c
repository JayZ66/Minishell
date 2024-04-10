/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 23:02:21 by romlambe          #+#    #+#             */
/*   Updated: 2024/04/09 16:54:21 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_clean_token	*clean_arg(t_token **token)
{
	t_clean_token	*clean_token = NULL;
	t_clean_token	*new = NULL;
	char			*arg = NULL;

	while (*token)
	{
		if ((*token)->type == ARG)
		{
			if (arg == NULL)
				arg = ft_strdup((*token)->content);
			else
			{
				char *temp = ft_strjoin(arg, " ");
				free(arg);
				arg = ft_strjoin(temp, (*token)->content);
				free(temp);
			}
		}
		else if (arg != NULL)
		{
			if (clean_token == NULL)
			{
				clean_token = init_clean_node(arg);
				new = clean_token;
			}
			else
			{
				new->next = init_clean_node(arg);
				new = new->next;
			}
			free(arg);
			arg = NULL;
		}
		*token = (*token)->next;
	}

	if (arg != NULL)
	{
		if (clean_token == NULL)
			clean_token = init_clean_node(arg);
		else
			new->next = init_clean_node(arg);
		free(arg);
	}

	return (clean_token);
}

t_clean_token	*clean_arg(t_token **token)
{
	t_clean_token	*clean_token = NULL;
	t_clean_token	*new = NULL;
	char			*arg = NULL;
	char			*temp = NULL;
	while(*token)
	{
		if((*token)->type == ARG && (*token)->next->type == INPUT)
		{
			if (arg == NULL)
			{
				arg = ft_strdup((*token)->content);

				*token = (*token)->next;
			}
			else
				temp = ft_strjoin(arg, " ");
				free(arg);
				arg = ft_strjoin(temp, (*token)->content);
				free(temp);

		}
		else if ((*token)->type == INPUT && (*token)->next->type == ARG)
		{
			
		}
	}
}


t_clean_token	*clean_space(t_clean_token **clean_token)
{
	size_t	i;
	size_t	j;
	int		flag;
	char	*temp;

	i = 0;
	j = 0;
	flag = 0;
	temp = (char *)malloc(ft_strlen((*clean_token)->content) + 1);
	while (*clean_token)
	{
		if (temp == NULL)
		{
			perror("Erreur de memoire");
			exit(EXIT_FAILURE);
		}
		ft_memset(temp, 0, ft_strlen((*clean_token)->content) + 1);
		while (j < ft_strlen((*clean_token)->content))
		{
			if ((*clean_token)->content[j] == ' ' || (*clean_token)->content[j] == '\t')
				flag = 1;
			if (!((*clean_token)->content[j] == ' ' || (*clean_token)->content[j] == '\t'))
			{
				if (flag == 1)
				{
					temp[i++] = ' ';
					flag = 0;
				}
				temp[i++] = (*clean_token)->content[j];
			}
		}
		temp[i] = '\0';
		free((*clean_token)->content);
		(*clean_token)->content = temp;
		(*clean_token) = (*clean_token)->next;
	}
	return (*clean_token);
}


