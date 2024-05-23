/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:04:14 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/23 18:04:03 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// char	*get_current_pwd(char **env)
// {
//     while (*env)
//     {
//         if (strncmp(*env, "PWD=", 4) == 0)
//         {
//             return (ft_strdup(*env + 4));
//         }
//         env++;
//     }
//     return (NULL);
// }

// char	**env_with_new_var(char **env, const char *var, const char *value)
// {
// 	size_t	i;
// 	char	**new_env;
// 	size_t	var_len;
// 	char	*new_var;
// 	int		var_found;

// 	i = 0;
// 	var_found = 0;
// 	var_len = ft_strlen(var);
// 	new_var = (char *)malloc(var_len + ft_strlen(value) + 2);
// 	if (!new_var)
// 		exit(EXIT_FAILURE);  // En cas d'échec de malloc
// 	ft_string_cpy(new_var, var);
// 	ft_strcat(new_var, "=", 1);
// 	ft_strcat(new_var, value, ft_strlen(value));
// 	while (env[i])
// 		i++;
// 	new_env = (char **)malloc(sizeof(char *) * (i + 2));  // +1 pour la nouvelle var., +1 pour NULL
// 	if (!new_env)
// 	{
// 		free(new_var);
// 		exit(EXIT_FAILURE);
// 	}
// 	i = 0;
// 	while (env[i])
// 	{
// 		if (strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
// 		{
// 			new_env[i] = new_var;
// 			var_found = 1;
// 		}
// 		else
// 		{
// 			new_env[i] = env[i];
// 			// free(env[i]);
// 		}
// 		i++;
// 	}
// 	if (!var_found)
// 	{
// 		new_env[i++] = new_var;
// 	}
// 	new_env[i] = NULL;
// 	// free(new_var);
// 	free(env);
// 	return (new_env);
// }

// char	**go_back_home(char **new_env, t_minishell *minishell)
// {
// 	// size_t	cwd_len;
// 	char	cwd[1024];
// 	char	*new_pwd;
// 	char	*old_pwd;

// 	old_pwd = get_current_pwd(minishell->env);
// 	if (old_pwd)
// 	{
// 		new_env = env_with_new_var(new_env, "OLDPWD", old_pwd);
// 		free(old_pwd);
// 	}
// 	if (chdir("/") != 0)
// 	{
// 		perror("Can't change directory\n");
// 		minishell->last_exit_status = EXIT_FAILURE;
// 		exit(EXIT_FAILURE);
// 	}
// 	// cwd_len = sizeof(cwd);
// 	if (getcwd(cwd, sizeof(cwd)) == NULL)
// 	{
// 		perror("Can't get the new path\n");
// 		// free(new_pwd);
// 		minishell->last_exit_status = EXIT_FAILURE;
// 		exit(EXIT_FAILURE);
// 	}
// 	new_pwd = (char *)malloc(ft_strlen("PWD=") + ft_strlen(cwd) + 1);
// 	if (!new_pwd)
// 	{
// 		minishell->last_exit_status = EXIT_FAILURE;
// 		exit(EXIT_FAILURE);
// 	}
// 	ft_string_cpy(new_pwd, "PWD=");
// 	ft_strcat(new_pwd, cwd, ft_strlen(cwd));
// 	new_env = env_with_new_var(new_env, "PWD", cwd);
// 	free(new_pwd);
// 	return (new_env);
// }

// char	**env_with_new_pwd(char **new_env, t_minishell *minishell, char *new_pwd)
// {
// 	size_t	i;

// 	i = 0;
// 	while (minishell->env[i])
// 	{
// 		if (ft_strcmp(minishell->env[i], "PWD=") == 0)
// 		{
// 			new_env[i] = new_pwd;
// 			// free(env[i]);
// 		}
// 		else
// 		{
// 			new_env[i] = minishell->env[i];
// 			// free(env[i]);
// 		}
// 		i++;
// 	}
// 	new_env[i] = NULL;
// 	// free(env);
// 	return (new_env);
// }

int	check_slash(char *cmd)
{
	size_t	i;
	int		count_slash;

	i = 0;
	count_slash = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			count_slash++;
		i++;
	}
	if (count_slash == 2)
	{
		ft_putstr_fd("//\n", 1);
		return (1);
	}
	else if (count_slash > 2 || count_slash == 1)
	{
		ft_putstr_fd("/\n", 1);
		return (1);
	}
	return (0);
}

int	check_cd_errors(char **cmd, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	int		one_point;

	i = -1;
	one_point = 0;
	// if (!cmd[1])
	// 	return (0);
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cmd[i][j + 1] && ft_isalpha(cmd[i][j]) == 1 
                && (cmd[i][j + 1] == '.' || cmd[i][j + 1] == '?'))
			{
				printf("Command '%s' not found\n", cmd[i]);
				return (1);
			}
			else if (cmd[i][j + 1] && (cmd[i][j] == '.' && cmd[i][j + 1] == '/'))
				return (1);
			else if (cmd[1][j] == '/')
			{
				if (check_slash(cmd[i]) == 1)
				{
					go_back_home(minishell);
					return (1);
				}
			}
			else if (cmd[1] && (cmd[1][j] == '.'  || cmd[i][j] == '/'))
				one_point++;
		}
	}
	if (one_point == 2)
		return (1);
	return (0);
}

// // Go to the home if cmd[1] doesn't exist
// // Check if we need the all cmd ou just path.
// // Chdir : Moving from a dir. to another one.
// // Getcwd : Récupérer le new path où on est.
// void	builtin_cd(t_minishell *minishell, char **cmd)
// {
// 	char	**new_env;

// 	new_env = minishell->env;
// 	if (check_cd_errors(cmd, new_env, minishell) == 1)
// 	{
// 		// free_tab(new_env);
// 		return ;
// 	}
// 	if (cmd[1] == NULL)
// 	{
// 		minishell->env = go_back_home(new_env, minishell);
// 		// free_tab(new_env);
// 		return ;
// 	}
// 	if (cmd[1] != NULL && is_relative_path(cmd) == 0)
// 	{
// 		cmd[1] = relative_to_absolute_path(cmd, minishell);
// 		if (!cmd[1])
// 		{
// 			// free_tab(new_env);
// 			// free(cmd[1]);
// 			return ;
// 		}
// 	}
// 	minishell->env = get_new_pwd(minishell, new_env, cmd);
// 	if (minishell->env == NULL)
// 		return ;
// 	// free(cmd[1]);
// 	// free_tab(new_env);
// 	return ;
// }


// char	**get_new_pwd(t_minishell *minishell, char **new_env, char **cmd)
// {
// 	char	cwd[1024];
// 	char old_cwd[1024];
// 	// size_t	cwd_len;

// 	// cwd_len = ft_strlen(cmd[1]) + 1;
// 	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
//     {
//         perror("getcwd");
//         return NULL;
//     }
// 	if (cmd[1] != NULL)
// 	{
// 		if (chdir(cmd[1]) != 0)
// 		{
// 			printf("bash: cd: No such file or directory\n");
// 			return (NULL);
// 		}
// 		if (getcwd(cwd, sizeof(cwd)) == NULL)
// 		{
// 			perror("Can't get the new path\n");
// 			return (NULL);
// 		}
// 	}
// 	new_env = change_pwd_env(minishell, new_env, cwd, old_cwd);
// 	return (new_env);
// }

// char **change_pwd_env(t_minishell *minishell, char **new_env, char *cwd, char *old_cwd)
// {
//     size_t i;
//     char *new_pwd;
//     char *new_oldpwd;
//     char **env;
//     int found_oldpwd = 0;
//     int found_pwd = 0;

//     i = 0;
//     env = minishell->env;

//     new_pwd = (char *)malloc(ft_strlen(cwd) + 5); // "PWD=" + cwd + null terminator
//     if (!new_pwd)
//     {
//         minishell->last_exit_status = EXIT_FAILURE;
//         exit(EXIT_FAILURE);
//     }
//     ft_string_cpy(new_pwd, "PWD=");
//     ft_strcat(new_pwd, cwd, ft_strlen(cwd));
//     new_oldpwd = (char *)malloc(ft_strlen(old_cwd) + 8); // "OLDPWD=" + old_cwd + null terminator
//     if (!new_oldpwd)
//     {
//         free(new_pwd);
//         minishell->last_exit_status = EXIT_FAILURE;
//         exit(EXIT_FAILURE);
//     }
//     ft_string_cpy(new_oldpwd, "OLDPWD=");
//     ft_strcat(new_oldpwd, old_cwd, ft_strlen(old_cwd));
//     while (env[i])
//     {
//         if (strcmp(env[i], "PWD=") == 0)
//         {
//             new_env[i] = new_pwd;
//             found_pwd = 1;
//         }
//         else if (strcmp(env[i], "OLDPWD=") == 0)
//         {
//             new_env[i] = new_oldpwd;
//             found_oldpwd = 1;
//         }
//         else
//         {
//             new_env[i] = env[i];
//         }
//         i++;
//     }
//     if (!found_pwd)
//         new_env[i++] = new_pwd;
//     if (!found_oldpwd)
//         new_env[i++] = new_oldpwd;
//     new_env[i] = NULL;
// 	free(new_pwd);
//     return (new_env);
// }

void go_back_home(t_minishell *minishell)
{
    char cwd[1024];
    char old_cwd[1024];

    if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
    {
        perror("getcwd");
        minishell->last_exit_status = EXIT_FAILURE;
        return;
    }

    if (chdir("/") != 0)
    {
        perror("Can't change directory\n");
        minishell->last_exit_status = EXIT_FAILURE;
        return;
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("Can't get the new path\n");
        minishell->last_exit_status = EXIT_FAILURE;
        return;
    }

    // Met à jour PWD et OLDPWD
    env_with_new_var(&(minishell->env), "OLDPWD", old_cwd);
    env_with_new_var(&(minishell->env), "PWD", cwd);
}


void env_with_new_var(char ***env, const char *var, const char *value)
{
    size_t i;
    size_t var_len;
    char *new_var;
    char **new_env;

    var_len = ft_strlen(var);
    new_var = (char *)malloc(var_len + ft_strlen(value) + 2);
    if (!new_var)
        exit(EXIT_FAILURE);  // En cas d'échec de malloc

    ft_string_cpy(new_var, var);
    ft_strcat(new_var, "=", 1);
    ft_strcat(new_var, value, ft_strlen(value));
    
    for (i = 0; (*env)[i]; i++)
    {
        if (strncmp((*env)[i], var, var_len) == 0 && (*env)[i][var_len] == '=')
        {
            // libérer l'ancienne variable d'environnement si elle a été allouée dynamiquement
            if ((*env)[i] != NULL) {
                free((*env)[i]);
            }
            (*env)[i] = new_var;
            return;
        }
    }
    // Si la variable n'est pas trouvée, ajouter une nouvelle entrée
    new_env = realloc(*env, sizeof(char *) * (i + 2));
    if (!new_env)
    {
        free(new_var);
        exit(EXIT_FAILURE);
    }
    new_env[i] = new_var;
    new_env[i + 1] = NULL;
    *env = new_env;
}


void change_pwd_env(t_minishell *minishell, const char *cwd, const char *old_cwd)
{
    env_with_new_var(&(minishell->env), "PWD", cwd);
    env_with_new_var(&(minishell->env), "OLDPWD", old_cwd);
}

void get_new_pwd(t_minishell *minishell, char **cmd)
{
    char cwd[1024];
    char old_cwd[1024];

    if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
    {
        perror("getcwd");
        return;
    }
    if (cmd[1] != NULL)
    {
        if (chdir(cmd[1]) != 0)
        {
            printf("bash: cd: No such file or directory\n");
            return;
        }
        if (getcwd(cwd, sizeof(cwd)) == NULL)
        {
            perror("Can't get the new path\n");
            return;
        }
    }
    change_pwd_env(minishell, cwd, old_cwd);
}


void builtin_cd(t_minishell *minishell, char **cmd)
{
    if (cmd[1] == NULL)
    {
        if (ft_strcmp(cmd[0], "cd") != 0) // Checker si / file sinon cmd not found !
		    printf("bash: %s: No such file or directory\n", cmd[0]);
        go_back_home(minishell);
        return;
    }
    if (check_cd_errors(cmd, minishell) == 1)
        return;
    if (cmd[1] != NULL && is_relative_path(cmd) == 0)
    {
        cmd[1] = relative_to_absolute_path(cmd, minishell);
        if (!cmd[1])
        {
            return;
        }
    }
    get_new_pwd(minishell, cmd);
}

//cdLibft/ => bash: cdLibft/: No such file or directory