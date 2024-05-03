/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 11:11:30 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/03 17:54:00 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	is_var_env(const char c)
{
	int	is_var_env;
	int	is_second_quote;

	is_var_env = 0;
	is_second_quote = 0;
	if (c == '$')
		is_var_env = 1;
	if (c == '"')
		is_second_quote = 1;
	if ((is_var_env == 1) && (is_second_quote == 1))
		return (0);
	return (1);
}

int	if_quote(char *var_env)
{
	int		quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (var_env[i])
	{
		if (var_env[i] == '"' || var_env[i] == '\'')
			quote = 1;
		i++;
	}
	return (quote);
}

char	**clean_spaces(char **args)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = -1;
	while (args[++i])
	{
		j = -1;
		k = 0;
		if (ft_strnchr(args[i], '=') == 0)
			args[i] = args[i];
		else
		{
			while (args[i][++j])
			{
				if (args[i][j] != 32)
				{
					args[i][k] = args[i][j];
					k++;
				}
			}
			args[i][k] = '\0';
		}
	}
	return (args);
}

int	is_something_after_equal(char *str)
{
	size_t	i;
	int		is_equal;

	i = 0;
	is_equal = 0;
	while (str[i])
	{
		if (str[i] == '=')
			is_equal = 1;
		else if (is_equal == 1 && str[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}
