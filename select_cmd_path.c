/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slect_path_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 19:50:35 by marvin            #+#    #+#             */
/*   Updated: 2024/03/25 19:50:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*select_path(char *cmd, char **env)
{
	char	**all_path;
	char	*part_path;
	char	*final_path;
	size_t	i;

	all_path = get_path(env);
	while (all_path[i])
	{
		part_path = ft_strjoin(all_path[i], "/");
		final_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(final_path, X_OK | F_OK) == 0)
			return (free_tab(all_path), final_path);
		free(final_path);
		i++;
	}
	free_tab(all_path);
	perror("Can't execute the cmd\n");
	return (NULL);
}

char	**get_path(char **env)
{
	size_t	i;
	size_t	j;
	char	*str;
	char	**path;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			if (env[i][j] == '=')
			{
				str = ft_substr(env[i], 0, j);
				if (ft_strcmp(str, "PATH") == 0)
				{
					j++;
					path = ft_split(env[i] + j, ':');
					free(str);
					return (path);
				}
				free(str);
			}
			j++;
		}
		i++;
	}
	return (perror("Can't get path\n"), NULL);
}