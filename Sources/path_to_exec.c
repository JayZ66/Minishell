/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_to_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:41:47 by marvin            #+#    #+#             */
/*   Updated: 2024/04/14 18:41:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char *cmd, t_minishell *minishell)
{
	char	*tmp_path;
	char	*final_path;
	char	**path;
	size_t	i;

	if (cmd == NULL)
		return (NULL);
	path = select_path(minishell, cmd);
	i = -1;
	if (!path)
	{
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	while (path[++i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		final_path = ft_strjoin(tmp_path, cmd);
		ft_free(tmp_path);
		if (access(final_path, X_OK) == 0)
			return (ft_free(path), final_path);
		ft_free(final_path);
	}
	return (ft_free(path), minishell->last_exit_status = 127,
		printf("bash: %s: command not found\n", cmd), NULL);
}

char	**select_path(t_minishell *minishell, char *cmd)
{
	size_t	i;
	size_t	j;
	char	**all_path;

	i = 0;
	while (minishell->env[i])
	{
		j = 0;
		while (minishell->env[i][j])
		{
			if (minishell->env[i][j] == '=')
			{
				if (ft_strncmp(minishell->env[i], "PATH", 4) == 0)
				{
					j++;
					all_path = ft_split(minishell->env[i] + j, ':');
					return (all_path);
				}
			}
			j++;
		}
		i++;
	}
	return (minishell->last_exit_status = 127,
		printf("bash: %s: command not found\n", cmd), NULL);
}
