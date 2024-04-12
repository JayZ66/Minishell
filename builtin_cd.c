/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:32:20 by marvin            #+#    #+#             */
/*   Updated: 2024/04/12 17:32:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_relative_path(char **cmd)
{
	size_t	i;
	size_t	is_absolute;

	is_absolute = 0;
	if (cmd[1] != NULL)
	{
		i = 0;
		while(cmd[1][i])
		{
			if (cmd[1][0] == '/')
			{
				is_absolute = 1;
				break ;
			}
			else
				break ;
			i++;
		}
	}
	printf("Path : %ld", is_absolute);
	return (is_absolute);
}

char	*relative_to_absolute_path(char **cmd)
{
	char	cwd[1024];
	char	*partial_path;
	char	*final_path;

	if (getcwd(cwd, 1024) == NULL) // Check buffer size !
	{
		perror("Can't get the new path\n");
		exit(EXIT_FAILURE);
	}
	partial_path = ft_strjoin(cwd, "/");
	final_path = ft_strjoin(partial_path, cmd[1]);
	free(partial_path);
	return (final_path);
}

// pour cd .. retirer ce qu'il y a droite de mon path (after /).
// A chaque fois que je rencontre ..
// Check s'il y a qqe chose avant le / (pas la racine ! = error)

// Prendre le path où je suis, retirer la fin,
// en vérifiant que c'est pas la racine. et mettre à jour
// le nouveau path (chdir). et le récupérer avec getcwd
// return cwd.
char	**handle_back(char **cmd, char **env, char **new_env)
{
	size_t	i;
	size_t	cwd_len;
	char	cwd[1024];
	char	*new_pwd;

	i = 0;
	if (getcwd(cwd, cwd_len) == NULL)
	{
		perror("Can't get our path\n");
		free_tab(new_env);
	}
	while (cwd[i])
		i++;
	while (cwd[i] != '/')
		i--;
	cwd = ft_substr(cwd + i, i, ft_strlen(cwd + i));
	if (!cwd)
	{
		perror("Substr error\n");
		exit(EXIT_FAILURE);
	}
	cwd_len = ft_strlen(cwd);
	new_pwd = (char *)malloc(sizeof(char) * (cwd_len + 5));
	if (!new_pwd)
	{
		perror("Can't allocate memory for the path\n");
		exit(EXIT_FAILURE);
	}
	if (cwd != NULL)
	{
		if (chdir(cwd) != 0) // Moving from a dir. to another one.
		{
			perror("Can't moove to the new directory\n");
			free(new_pwd);
			exit(EXIT_FAILURE);
		}
		if (getcwd(cwd, cwd_len) == NULL) // Récupérer le new path où on est.
		{
			perror("Can't get the new path\n");
			free(new_pwd);
			exit(EXIT_FAILURE);
		}
	}
	ft_string_cpy(new_pwd, "PWD=");
	ft_strcat(new_pwd, cwd, cwd_len);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			// ft_string_cpy(new_env[i], new_pwd);
			new_env[i] = new_pwd; // Update le path dans l'env.
			free(env[i]);
			// free(new_pwd);
		}
		else
		{
			new_env[i] = ft_strdup(env[i]);
			free(env[i]);
		}
		i++;
	}
	free(env);
	new_env[i] = NULL;
	return (new_env);
}


char	**builtin_cd(char **env, char **cmd) // Check if we need the all cmd ou just path.
{
	size_t	i;
	size_t	cwd_len;
	char	cwd[1024]; // To change & alloc the right size.
	char	*new_pwd;
	char	**new_env;

	if (is_relative_path(cmd) == 0)
		cmd[1] = relative_to_absolute_path(cmd);
	i = 0;
	cwd_len = ft_strlen(cmd[1]);
	new_env = (char **)malloc(sizeof(char *) * (ft_size_env(env) + 1));
	if (!new_env)
	{
		perror("Can't allocate memory for the env\n");
		exit(EXIT_FAILURE);
	}
	if (cmd[1] == '..')
	{
		new_env = handle_back(cmd, cwd, env, new_env);
		return (new_env);
	}
	new_pwd = (char *)malloc(sizeof(char) * (cwd_len + 5));
	if (!new_pwd)
	{
		perror("Can't allocate memory for the path\n");
		exit(EXIT_FAILURE);
	}
	if (cmd[1] != NULL)
	{
		if (chdir(cmd[1]) != 0) // Moving from a dir. to another one.
		{
			perror("Can't moove to the new directory\n");
			free(new_pwd);
			exit(EXIT_FAILURE);
		}
		if (getcwd(cwd, cwd_len) == NULL) // Récupérer le new path où on est.
		{
			perror("Can't get the new path\n");
			free(new_pwd);
			exit(EXIT_FAILURE);
		}
	}
	ft_string_cpy(new_pwd, "PWD=");
	ft_strcat(new_pwd, cwd, cwd_len);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			// ft_string_cpy(new_env[i], new_pwd);
			new_env[i] = new_pwd; // Update le path dans l'env.
			free(env[i]);
			// free(new_pwd);
		}
		else
		{
			new_env[i] = ft_strdup(env[i]);
			free(env[i]);
		}
		i++;
	}
	free(env);
	new_env[i] = NULL;
	return (new_env);
}

// Coller le chemin relatif à l'absolute path du
// dossier courant avant de l'utiliser pour cd