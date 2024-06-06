/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 18:01:22 by marvin            #+#    #+#             */
/*   Updated: 2024/04/13 18:01:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	lst_size(t_token *token)
{
	size_t	count;

	count = 0;
	if (!token)
	{
		perror("List is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token)
	{
		token = token->next;
		count++;
	}
	return (count);
}

void	free_tab(char **tab)
{
	int	i;

	if (tab == NULL)
		return ;
	i = 0;
	while (tab[i])
	{
		if (tab[i] != NULL)
			ft_free(tab[i]);
		i++;
	}
	ft_free(tab);
}

int	ft_strlen_tab(char **cmd_line)
{
	size_t	i;

	i = 0;
	while (cmd_line[i])
		i++;
	return (i);
}

int	ft_lstsize_content(t_token *token)
{
	size_t	total_length;
	t_token	*temp;

	total_length = 0;
	temp = token;
	while (temp != NULL)
	{
		total_length += ft_strlen(token->content);
		temp = temp->next;
	}
	return (total_length);
}

char	**split_cmd(char *var_env)
{
	char	**args;

	args = NULL;
	args = ft_split(var_env, ' ');
	return (args);
}
