/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:06:47 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/01 16:08:24 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*extract_of_the_var(char *str)
{
	size_t	len;
	char	*var;

	len = len_of_var_of_env(str + 1);
	var = (char *)malloc(len + 2);
	if (var == NULL)
		return (NULL);
	strncpy(var, str, len + 1);
	var[len + 1] = '\0';
	return (var);
}

//gerer les msg d'erreur-> 2 msg (voir ou ce situe le second)
char	*select_var_of_env(t_minishell *minishell, char *cmd)
{
	size_t	i;
	size_t	j;
	char	*all_path;

	i = 0;
	while (minishell->env[i])
	{
		j = 0;
		while (minishell->env[i][j])
		{
			if (minishell->env[i][j] == '=')
			{
				if (ft_strncmp(minishell->env[i], cmd, ft_strlen(cmd)) == 0)
				{
					j++;
					all_path = ft_strdup(minishell->env[i] + j);
					return (all_path);
				}
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

void	replace_var_of_env(char *content, char *var, int i)
{
	if (content[i] == 0)
		content = ft_strdup(var);
	else
		content = ft_strjoin(var, content + i);
}

int	len_of_var_of_env(char *str)
{
	int	len;

	len = 0;
	while (str[len] && (isalnum(str[len]) || str[len] == '_'))
		len++;
	return (len);
}
