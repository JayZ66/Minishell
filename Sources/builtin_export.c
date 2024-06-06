/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:12:21 by marvin            #+#    #+#             */
/*   Updated: 2024/04/02 22:12:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	modify_value_env(char ***env, const char *var, const char *value,
	t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	char	*new_entry;

	i = 0;
	if (reset_existing_value(var, value, minishell, env) == 1)
		return ;
	while ((*env)[i])
	{
		j = 0;
		while ((*env)[i][j] && var[j] && (*env)[i][j] == var[j])
			j++;
		if (var[j] == '\0' && (*env)[i][j - 1] == '=')
		{
			new_entry = copy_new_value(var, value, minishell);
			ft_free((*env)[i]);
			(*env)[i] = new_entry;
			return ;
		}
		i++;
	}
}

char	**new_export_env(t_minishell *minishell, size_t size_env)
{
	size_t	i;
	char	**new_env;

	i = -1;
	new_env = (char **)ft_malloc(sizeof(char *) * (size_env + 2));
	if (!new_env)
	{
		perror("Can't create the new env.\n");
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	while (++i < size_env)
	{
		new_env[i] = ft_strdup(minishell->env[i]);
		if (!new_env[i])
		{
			perror("Can't copy environment variable.\n");
			ft_free(new_env);
			minishell->last_exit_status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
	}
	return (new_env);
}

char	**create_var_env(t_minishell *minishell, char *var)
{
	size_t	size_env;
	size_t	i;
	char	**new_env;

	size_env = ft_size_env(minishell->env);
	new_env = new_export_env(minishell, size_env);
	new_env[size_env] = ft_strdup(var);
	if (!new_env[size_env])
	{
		perror("Can't copy new environment variable.\n");
		i = -1;
		while (++i < size_env)
			ft_free(new_env[i]);
		ft_free(new_env);
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	new_env[size_env + 1] = NULL;
	return (ft_free(minishell->env), new_env);
}

void	manage_export_modification(char **args, t_minishell *minishell)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (identifier_errors_export(args[i]) == 1)
		{
			if (args[i + 1] == NULL)
				break ;
			i++;
		}
		while (args[i][j])
		{
			if (args[i][j] == '=')
			{
				modify_or_create(args, minishell, i, j);
				if (args[i + 1] == NULL)
					break ;
			}
			j++;
		}
	}
}

void	builtin_export(char **args, t_minishell *minishell)
{
	if (args[1] != NULL)
		manage_export_modification(args, minishell);
	else if (ft_strcmp(args[0], "export") != 0)
		return ;
	else
		print_export_env(minishell);
}
