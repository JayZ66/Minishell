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

	i = 0;
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

// Don't forget to handle quotes !!
// char	*get_the_var_of_env(t_token *node)
// {
// 	t_token	*tmp;
// 	char	*var_env;
// 	char	*result;
// 	size_t	i;

// 	tmp = node;
// 	while (tmp)
// 	{
// 		i = 0;
// 		while (tmp->content[i])
// 		{
// 			if (tmp->content[i] == '$')
// 			{
// 				i++;
// 				var_env = ft_substr(tmp->content + i, 0, ft_strlen(tmp->content + i));
// 				if (ft_strncmp(var_env, "PATH", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "MANPATH", 7) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "SHELL", 5) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "NAME", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "PWD", 3) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LOGNAME", 7) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "HOME", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LANG", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LS_COLORS", 9) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "WAYLAND_DISPLAY", 16) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LESSCLOSE", 9) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "TERM", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "LESSOPEN", 8) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "USER", 4) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "DISPLAY", 7) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "SHLVL", 5) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "XDG_RUNTIME_DIR", 15) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "XDG_DATA_DIRS", 13) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "DBUS_SESSION_BUS_ADRESS", 23) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "HOSTTYPE", 8) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				else if (ft_strncmp(var_env, "PULSE_SERVER", 12) == 0)
// 					return (result = getenv(var_env), free(var_env), result);
// 				free(var_env);
// 			}
// 			i++;
// 		}
// 		tmp = tmp->next;
// 	}
// 	perror("Can't get this var. from the env.\n");
// 	return (NULL);
// }