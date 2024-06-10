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

int	is_var_in_env(char *var, t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0)
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

void	modify_or_create(char **args, t_minishell *minishell,
	size_t i, size_t j)
{
	char	*var;
	char	*new_var;

	new_var = ft_substr(args[i], 0, j + 1);
	if (is_var_in_env(new_var, minishell) == 1)
	{
		var = check_value(args[i], minishell);
		if (ft_strcmp(args[i], var) != 0)
			ft_free(new_var);
		modify_value_env(&minishell->env, new_var, args[i] + j + 1, minishell);
		ft_free(new_var);
	}
	else
	{
		var = check_value(args[i], minishell);
		minishell->env = create_var_env(minishell, var);
		if (ft_strcmp(args[i], var) != 0)
			ft_free(var);
		ft_free(new_var);
	}
}

char	*check_value(char *var, t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '!')
		{
			printf("bash: %s: event not found\n", var + i);
			return (ft_substr(var, 0, i));
		}
		else if (var[i] == ';')
		{
			minishell->last_exit_status = 127;
			printf("bash: %s: command not found\n", var + i);
			return (ft_substr(var, 0, i));
		}
		i++;
	}
	return (var);
}
