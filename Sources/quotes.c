/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:05:34 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 18:10:36 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remove_first_level_quote(char *content)
{
	int		i;
	int		j;
	int		single_quote;
	int		double_quote;
	char	*temp;

	i = 0;
	j = 0;
	single_quote = 0;
	double_quote = 0;
	temp = (char *)ft_malloc(ft_strlen(content) + 1);
	if (!temp)
		return (perror("malloc"), NULL);
	while (content[i])
	{
		if (content[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (content[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else
			temp[j++] = content[i];
		i++;
	}
	temp[j] = '\0';
	return (temp);
}

void	update_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '\"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

void	remove_quote(t_final_token *token)
{
	while (token)
	{
		token->content = remove_first_level_quote(token->content);
		token = token->next;
	}
}
