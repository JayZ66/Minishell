/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 15:35:20 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/25 18:11:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
ReplaceEnvVars
*/
// How to replace the var. in the list ?
// Should we send the node->content ?
// How do we change the value of the node->content ?

char	*extract_var(char *str)
{
	size_t	i;
	char	*var_env;
	char	*result;

	i = 0;
	if (str[i] == '$')
	{
		i++;
		var_env = ft_substr(str + i, 0, ft_strlen(str + i));
		result = getenv(var_env);
		if (result == NULL)
			return (perror("This var. is not existing in the env.\n"),
				free(var_env), NULL);
		return (free(var_env), result);
	}
	perror("Can't get the var. of env.");
	return (NULL);
}

int	check_var(t_final_token *node)
{
	t_final_token	*tmp;
	size_t			i;

	tmp = node;
	while (tmp)
	{
		i = -1;
		while (tmp->content[++i])
		{
			if (tmp->content[i] == '"')
			{
				while (tmp->content[i])
				{
					if (is_var_env(tmp->content[i]) == 0)
						return (0);
					i++;
				}
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*get_the_var_of_env(t_final_token *node, t_minishell *minishell)
{
	t_final_token	*tmp;
	char			*var;
	size_t			i;

	tmp = node;
	if (check_var(node) == 1)
	{
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	while (tmp)
	{
		i = -1;
		while (tmp->content[++i])
		{
			while (tmp->content[i++] == ' ')
				i++;
			var = extract_var(tmp->content + i);
			if (!var)
				return (NULL);
			return (var);
		}
		tmp = tmp->next;
	}
	return (perror("Can't get this var.\n"), NULL);
}
