/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:37:09 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/06 11:29:01 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	read_here_doc(size_t i, char **limiter)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (ft_strncmp_limiter(line, limiter[i], ft_strlen(limiter[i])) == 0)
		{
			ft_free(line);
			return ;
		}
		ft_putstr_fd(line, 1);
		ft_free(line);
	}
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
