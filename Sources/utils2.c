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

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int	manage_file(int nb_args, char **cmd_line, int flag)
{
	int	first_file;
	int	last_file;

	first_file = 0;
	last_file = 0;
	if (flag == 2)
		last_file = open(cmd_line[nb_args - 1], O_WRONLY
				| O_CREAT | O_APPEND, 0644);
	else if (flag == 1)
		last_file = open(cmd_line[nb_args - 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
	else if (flag == 0)
		first_file = open(cmd_line[0], O_RDONLY, 0644);
	if (last_file == -1 || first_file == -1)
		return (perror("Can't open file\n"), exit(EXIT_FAILURE), 1);
	else if (last_file)
		return (last_file);
	else if (first_file)
		return (first_file);
	return (1);
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
