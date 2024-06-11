/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:11:27 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:10 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	replace_content_middle(t_final_token *tmp,
	char *env_value, size_t i, int len)
{
	char	*temp;
	char	*final;

	temp = ft_strndup(tmp->content, i);
	if (!temp)
		return (0);
	final = ft_malloc(strlen(temp) + ft_strlen(env_value)
			+ ft_strlen(tmp->content + i + len + 1) + 1);
	if (!final)
		return (0);
	ft_string_cpy(final, temp);
	ft_strcat(final, env_value, ft_strlen(env_value));
	ft_strcat(final, tmp->content + i + len + 1,
		ft_strlen(tmp->content + i + len + 1));
	ft_free(tmp->content);
	tmp->content = final;
	return (1);
}

char	*erase_dollar(char *content, int i)
{
	while (content[i])
	{
		content[i] = content[i + 1];
		i++;
	}
	return (content);
}

void	process_token_content(t_final_token *tmp, t_minishell *minishell,
	int *in_single_quote, int *in_double_quote)
{
	size_t	i;

	i = 0;
	while (tmp->content[i])
	{
		update_quotes(tmp->content[i], in_single_quote, in_double_quote);
		if (tmp->content[i] == '$' && (tmp->content[i + 1] == ' '
				|| tmp->content[i + 1] == '\0' || tmp->content[i + 1] == '$'))
			return ;
		else if (tmp->content[i] == '$' && (tmp->content[i + 1] == '\''
				|| tmp->content[i + 1] == '"')
			&& (!(*in_double_quote) && (!(*in_single_quote))))
			tmp->content = erase_dollar(tmp->content, i);
		else if (tmp->content[i] == '$' && (!(*in_single_quote
					|| *in_double_quote)))
		{
			if (!handle_env_var(tmp, minishell, &i))
				return ;
		}
		i++;
	}
}
