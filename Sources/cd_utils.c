/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:47:14 by marvin            #+#    #+#             */
/*   Updated: 2024/05/24 11:47:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_slash(char *cmd)
{
	size_t	i;
	int		count_slash;

	i = 0;
	count_slash = 0;
	while (cmd[i])
	{
		if (ft_isalpha(cmd[0]) == 1 || ft_isalpha(cmd[1]) == 1)
			return (0);
		if (cmd[i] == '/')
			count_slash++;
		i++;
	}
	if (count_slash == 2)
		return (1);
	else if (count_slash > 2 || count_slash == 1)
		return (1);
	return (0);
}

int	cd_errors(char **cmd, size_t i, size_t j, t_minishell *minishell)
{
	if (cmd[i][j + 1] && ft_isalpha(cmd[i][j]) == 1
		&& (cmd[i][j + 1] == '.' || cmd[i][j + 1] == '?'))
		return (printf("Command '%s' not found\n", cmd[i]), 1);
	else if (cmd[i][j + 1] && (cmd[i][j] == '.'
		&& cmd[i][j + 1] == '.'))
		return (0);
	else if (cmd[1][j] == '/' )
	{
		if (check_slash(cmd[i]) == 1)
			return (go_back_home(minishell), 1);
	}
	return (0);
}

int	check_cd_errors(char **cmd, t_minishell *minishell)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cd_errors(cmd, i, j, minishell) == 1)
				return (1);
			else
				return (0);
		}
	}
	return (0);
}

int	is_var_existing(t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i])
	{
		if (ft_strncmp(minishell->env[i], "PWD", 3) == 0)
			return (1);
		else if (ft_strncmp(minishell->env[i], "OLDPWD", 6) == 0)
			return (2);
		i++;
	}
	return (0);
}

char	**alloc_new_env(size_t i, char *new_var, char **env)
{
	char	**new_env;

	new_env = ft_realloc(env, sizeof(char *) * (i + 2));
	if (!new_env)
	{
		ft_free(new_var);
		exit(EXIT_FAILURE);
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}
