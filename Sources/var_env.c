/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:03:05 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/04 14:15:16 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_var_of_env(t_final_token *node, t_minishell *minishell)
{
	t_final_token	*tmp;
	int				in_single_quote;
	int				in_double_quote;

	tmp = node;
	in_single_quote = 0;
	in_double_quote = 0;
	while (tmp)
	{
		if (get_exit_code(tmp->content, minishell) == 0)
			process_token_content(tmp, minishell, &in_single_quote,
				&in_double_quote);
		tmp = tmp->next;
	}
}

int	handle_env_var(t_final_token *tmp, t_minishell *minishell, size_t *i)
{
	char	*var;
	char	*env_value;
	int		len;

	len = len_of_var_of_env(tmp->content + *i + 1);
	var = extract_of_the_var(tmp->content + *i);
	if (var == NULL)
	{
		if (*var == '$')
			free(var);
		return (0);
	}
	env_value = select_var_of_env(minishell, var + 1);
	free(var);
	if (!env_value)
	{
		tmp->content = "";
		return (0);
	}
	if (*i == 0)
	{
		if (!replace_content_start(tmp, env_value))
		{
			free(env_value);
			return (0);
		}
	}
	else
	{
		if (!replace_content_middle(tmp, env_value, *i, len))
		{
			free(env_value);
			return (0);
		}
	}
	free(env_value);
	return (1);
}

int	replace_content_start(t_final_token *tmp, char *env_value)
{
	char	*new_content;

	new_content = realloc(tmp->content, strlen(env_value) + 1);
	if (!new_content)
		return (0);
	tmp->content = new_content;
	strcpy(tmp->content, env_value);
	return (1);
}

int	replace_content_middle(t_final_token *tmp,
	char *env_value, size_t i, int len)
{
	char	*temp;
	char	*final;

	temp = strndup(tmp->content, i);
	if (!temp)
		return (0);
	final = malloc(strlen(temp) + strlen(env_value)
			+ strlen(tmp->content + i + len + 1) + 1);
	if (!final)
	{
		// free(temp);
		return (0);
	}
	strcpy(final, temp);
	strcat(final, env_value);
	strcat(final, tmp->content + i + len + 1);
	// free(tmp->content);
	tmp->content = final;
	// free(final);
	// free(temp);
	return (1);
}

void	process_token_content(t_final_token *tmp, t_minishell *minishell,
	int *in_single_quote, int *in_double_quote)
{
	size_t	i;

	i = 0;
	while (tmp->content[i])
	{
		update_quotes(tmp->content[i], in_single_quote, in_double_quote);
		if (tmp->content[i] == '$' && !(*in_single_quote))
		{
			if (!handle_env_var(tmp, minishell, &i))
				return ;
		}
		i++;
	}
}
