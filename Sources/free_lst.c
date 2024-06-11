/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 16:53:51 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/11 17:32:25 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_lst_not_content(t_token **token)
{
	t_token	*tmp;

	if (!(*token))
	{
		perror("Lst is empty, can't free\n");
		exit(EXIT_FAILURE);
	}
	while (*token)
	{
		tmp = (*token)->next;
		ft_free(*token);
		*token = tmp;
	}
	*token = NULL;
}

void	free_lst_not_content_clean(t_clean_token **token)
{
	t_clean_token	*tmp;

	if (!(*token))
	{
		perror("Lst is empty, can't free\n");
		exit(EXIT_FAILURE);
	}
	while (*token)
	{
		tmp = (*token)->next;
		ft_free(*token);
		*token = tmp;
	}
	*token = NULL;
}
