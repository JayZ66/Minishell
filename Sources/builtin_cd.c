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

#include "../minishell.h"

char	**go_back_home(char **new_env, t_minishell *minishell)
{
	size_t	cwd_len;
	char	cwd[1024];
	char	*new_pwd;

	if (chdir(getenv("HOME")) != 0)
	{
		perror("Can't change directory\n");
		exit(EXIT_FAILURE);
	}
	cwd_len = 100;
	new_pwd = (char *)malloc(sizeof(char) * (cwd_len + 5));
	if (!new_pwd)
		exit(EXIT_FAILURE);
	if (getcwd(cwd, cwd_len) == NULL)
	{
		perror("Can't get the new path\n");
		free(new_pwd);
		exit(EXIT_FAILURE);
	}
	ft_string_cpy(new_pwd, "PWD=");
	ft_strcat(new_pwd, cwd, cwd_len);
	new_env = env_with_new_pwd(new_env, minishell, new_pwd);
	return (new_env);
}

char	**env_with_new_pwd(char **new_env, t_minishell *minishell, char *new_pwd)
{
	size_t	i;
	char	**env;

	env = minishell->env;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			new_env[i] = new_pwd;
			// free(env[i]);
		}
		else
		{
			new_env[i] = ft_strdup(env[i]);
			// free(env[i]);
		}
		i++;
	}
	new_env[i] = NULL;
	// free(env);
	return (new_env);
}

// Go to the home if cmd[1] doesn't exist
// Check if we need the all cmd ou just path.
// Chdir : Moving from a dir. to another one.
// Getcwd : Récupérer le new path où on est.
void	builtin_cd(t_minishell *minishell, char **cmd)
{
	char	**new_env;

	new_env = (char **)malloc(sizeof(char *) * (ft_size_env(minishell->env) + 1));
	if (!new_env)
	{
		perror("Can't allocate memory for the env\n");
		exit(EXIT_FAILURE);
	}
	if (cmd[1] == NULL)
	{
		minishell->env = go_back_home(new_env, minishell);
		free_tab(new_env);
		return ;
	}
	if (cmd[1] != NULL && is_relative_path(cmd) == 0)
	{
		cmd[1] = relative_to_absolute_path(cmd);
		if (!cmd[1])
		{
			free_tab(new_env);
			free(cmd[1]);
			return ;
		}
	}
	minishell->env = get_new_pwd(minishell, new_env, cmd);
	free(cmd[1]);
	free_tab(new_env);
	return ;
}

	// cwd_len = ft_strlen(cmd[1]) + 1;
	// new_pwd = (char *)malloc(sizeof(char) * (cwd_len + 5));
	// if (!new_pwd)
	// {
	// 	perror("Can't allocate memory for the path\n");
	// 	exit(EXIT_FAILURE);
	// }
	// if (cmd[1] != NULL)
	// {
	// 	if (chdir(cmd[1]) != 0)
	// 	{
	// 		perror("Can't moove to the new directory\n");
	// 		free(new_pwd);
	// 		exit(EXIT_FAILURE);
	// 	}
	// 	if (getcwd(cwd, cwd_len) == NULL)
	// 	{
	// 		perror("Can't get the new path\n");
	// 		free(new_pwd);
	// 		exit(EXIT_FAILURE);
	// 	}
	// }
	// ft_string_cpy(new_pwd, "PWD=");
	// ft_strcat(new_pwd, cwd, cwd_len);
	// while (env[i])
	// {
	// 	if (ft_strncmp(env[i], "PWD=", 4) == 0)
	// 	{
	// 		new_env[i] = new_pwd;
	// 		free(env[i]);
	// 	}
	// 	else
	// 	{
	// 		new_env[i] = ft_strdup(env[i]);
	// 		free(env[i]);
	// 	}
	// 	i++;
	// }
	// free(env);
	// new_env[i] = NULL;

char	**get_new_pwd(t_minishell *minishell, char **new_env, char **cmd)
{
	char	cwd[1024];
	size_t	cwd_len;

	cwd_len = ft_strlen(cmd[1]) + 1;
	if (cmd[1] != NULL)
	{
		if (chdir(cmd[1]) != 0)
		{
			perror("Can't moove to the new directory\n");
			exit(EXIT_FAILURE);
		}
		if (getcwd(cwd, cwd_len) == NULL)
		{
			perror("Can't get the new path\n");
			exit(EXIT_FAILURE);
		}
	}
	new_env = change_pwd_env(minishell, new_env, cwd_len, cwd);
	return (new_env);
}

char	**change_pwd_env(t_minishell *minishell, char **new_env, size_t cwd_len, char *cwd)
{
	size_t	i;
	char	*new_pwd;
	char	**env;

	i = -1;
	env = minishell->env;
	new_pwd = (char *)malloc(sizeof(char) * (cwd_len + 5));
	if (!new_pwd)
		exit(EXIT_FAILURE);
	ft_string_cpy(new_pwd, "PWD=");
	ft_strcat(new_pwd, cwd, cwd_len);
	while (env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			new_env[i] = new_pwd;
			// free(env[i]);
		}
		else
		{
			new_env[i] = ft_strdup(env[i]);
			// free(env[i]);
		}
	}
	// free(env);
	// free(new_pwd); Why ??
	new_env[i] = NULL;
	return (new_env);
}

// Coller le chemin relatif à l'absolute path du
// dossier courant avant de l'utiliser pour cd

// pour cd .. retirer ce qu'il y a droite de mon path (after /).
// A chaque fois que je rencontre ..
// Check s'il y a qqe chose avant le / (pas la racine ! = error)

// Prendre le path où je suis, retirer la fin,
// en vérifiant que c'est pas la racine. et mettre à jour
// le nouveau path (chdir). et le récupérer avec getcwd
// return cwd.

// char	**handle_back(char **env, char **new_env)
// {
// 	size_t	i;
// 	size_t	cwd_len;
// 	char	cwd[1024];
// 	char	*new_pwd;

// 	i = 0;
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		perror("Can't get our path\n");
// 		free_tab(new_env);
// 	}
// 	while (cwd[i])
// 		i++;
// 	while (cwd[i] != '/')
// 		i--;
// 	ft_string_cpy(cwd, ft_substr(cwd + i, i, ft_strlen(cwd + i)));
// 	if (cwd == NULL)
// 	{
// 		perror("Substr error\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	cwd_len = ft_strlen(cwd);
// 	new_pwd = (char *)malloc(sizeof(char) * (cwd_len + 5));
// 	if (!new_pwd)
// 	{
// 		perror("Can't allocate memory for the path\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (cwd != NULL)
// 	{
// 		if (chdir(cwd) != 0) // Moving from a dir. to another one.
// 		{
// 			perror("Can't moove to the new directory\n");
// 			free(new_pwd);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (getcwd(cwd, cwd_len) == NULL) // Récupérer le new path où on est.
// 		{
// 			perror("Can't get the new path\n");
// 			free(new_pwd);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	ft_string_cpy(new_pwd, "PWD=");
// 	ft_strcat(new_pwd, cwd, cwd_len);
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PWD=", 4) == 0)
// 		{
// 			// ft_string_cpy(new_env[i], new_pwd);
// 			new_env[i] = new_pwd; // Update le path dans l'env.
// 			free(env[i]);
// 			// free(new_pwd);
// 		}
// 		else
// 		{
// 			new_env[i] = ft_strdup(env[i]);
// 			free(env[i]);
// 		}
// 		i++;
// 	}
// 	free(env);
// 	new_env[i] = NULL;
// 	return (new_env);
// }