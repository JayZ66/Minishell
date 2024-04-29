/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 11:31:28 by marvin            #+#    #+#             */
/*   Updated: 2024/04/19 11:31:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Check if the var. is in the
existing environment.
*/

int	is_var_in_env(char *var, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_size_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

void	sort_tab(char **env)
{
	size_t	i;
	char	*temp;

	i = 0;
	while (env[i + 1])
	{
		if (env[i][0] > env[i + 1][0]
			|| (env[i][0] == env[i + 1][0] && env[i][1] > env[i + 1][1]))
		{
			temp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
}

char	**modify_or_create(char **args, char **env, size_t i, char **new_env)
{
	char	*var;
	size_t	j;

	j = 1;
	while (args[j])
	{
		var = ft_substr(args[j], 0, i);
		if (is_var_in_env(var, env) == 1)
		{
			new_env = modify_value_env(env, var, args[1] + i);
			free(var);
			return (new_env);
		}
		else
		{
			new_env = create_var_env(env, args[j]);
			free(var);
		}
		env = new_env;
		j++;
	}
	return (new_env);
}

char	**print_env(char **env)
{
	size_t	i;

	i = 0;
	sort_tab(env);
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (env);
}
