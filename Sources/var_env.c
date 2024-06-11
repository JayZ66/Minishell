/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:03:05 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/11 14:27:06 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rebuild_cmd_line(t_final_token *tmp, t_minishell *minishell)
{
	char	*nb;
	char	**cmd;

	cmd = ft_split(tmp->content, ' ');
	nb = ft_itoa(minishell->last_exit_status);
	if (cmd[1])
	{
		ft_string_cpy(tmp->content, cmd[0]);
		ft_strcat(tmp->content, " ", 1);
		ft_strcat(tmp->content, nb, ft_strlen(nb));
	}
	else if (!cmd[1])
	{
		tmp->content = nb;
	}
	free_tab(cmd);
}

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
		if (get_exit_code(tmp->content, minishell) == 1)
			rebuild_cmd_line(tmp, minishell);
		else
			process_token_content(tmp, minishell, &in_single_quote,
				&in_double_quote);
		tmp = tmp->next;
	}
}

int	extract_and_check_var(t_final_token *tmp, t_minishell *minishell,
	size_t *i, char **env_value)
{
	char	*var;
	int		len;
	char	*new_content;

	len = len_of_var_of_env(tmp->content + *i + 1);
	var = extract_of_the_var(tmp->content + *i);
	if (var == NULL || len == 0)
		return (ft_free(var), 0);
	*env_value = select_var_of_env(minishell, var + 1);
	ft_free(var);
	if (!*env_value)
	{
		if (*i == 0)
			tmp->content += len + 1;
		else
		{
			new_content = tmp->content;
			ft_memmove(new_content, tmp->content, *i);
			ft_string_cpy(new_content + *i, tmp->content + *i + len + 1);
			tmp->content = new_content;
		}
		return (0);
	}
	return (1);
}

int	handle_env_var(t_final_token *tmp, t_minishell *minishell, size_t *i)
{
	char	*env_value;
	int		len;

	if (!extract_and_check_var(tmp, minishell, i, &env_value))
		return (0);
	if (*i == 0)
	{
		if (!replace_content_start(tmp, env_value))
			return (ft_free(env_value), 0);
	}
	else
	{
		len = len_of_var_of_env(tmp->content + *i + 1);
		if (!replace_content_middle(tmp, env_value, *i, len))
			return (ft_free(env_value), 0);
	}
	return (ft_free(env_value), 1);
}

int	replace_content_start(t_final_token *tmp, char *env_value)
{
	tmp->content = ft_realloc(tmp->content, ft_strlen(env_value) + 1);
	if (!tmp->content)
		return (0);
	ft_string_cpy(tmp->content, env_value);
	return (1);
}
