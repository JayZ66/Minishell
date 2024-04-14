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

#include "minishell.h"

char	*get_path(char *cmd, char **env)
{
	char	*tmp_path;
	char	*final_path;
	char	**path;
	size_t	i;

	path = select_path(env);
	i = 0;
	if (!path)
		exit(EXIT_FAILURE);
	while (path[i])
	{
		tmp_path = ft_strjoin(path[i], "/");
		final_path = ft_strjoin(tmp_path, cmd);
		free(tmp_path);
		if (access(final_path, X_OK) == 0)
		{
			return (free_tab(path), final_path);
		}
		free(final_path);
		i++;
	}
	free_tab(path);
	perror("The executable doesn't exist in the repo\n");
	return (NULL);
}

char	**select_path(char **env)
{
	size_t	i;
	size_t	j;
	char	**all_path;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				if (ft_strncmp(env[i], "PATH", 4) == 0)
				{
					j++;
					all_path = ft_split(env[i] + j, ':');
					return (all_path);
				}
			}
			j++;
		}
		i++;
	}
	perror("Can't find the var. path in env.\n");
	return (NULL);
}
