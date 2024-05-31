/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:04:14 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/31 18:28:30 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	go_back_home(t_minishell *minishell)
{
	char	cwd[1024];
	char	old_cwd[1024];

	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
	{
		perror("getcwd");
		minishell->last_exit_status = EXIT_FAILURE;
		return ;
	}
	if (chdir("/") != 0)
	{
		perror("Can't change directory\n");
		minishell->last_exit_status = EXIT_FAILURE;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Can't get the new path\n");
		minishell->last_exit_status = EXIT_FAILURE;
		return ;
	}
	env_with_new_var(minishell->env, "OLDPWD", old_cwd);
	env_with_new_var(minishell->env, "PWD", cwd);
}

void	go_back_user(t_minishell *minishell)
{
	char	cwd[1024];
	char	old_cwd[1024];

	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
	{
		perror("getcwd");
		minishell->last_exit_status = EXIT_FAILURE;
		return ;
	}
	if (chdir("/home/jeguerin/") != 0)
	{
		perror("Can't change directory\n");
		minishell->last_exit_status = EXIT_FAILURE;
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Can't get the new path\n");
		minishell->last_exit_status = EXIT_FAILURE;
		return ;
	}
	env_with_new_var(minishell->env, "OLDPWD", old_cwd);
	env_with_new_var(minishell->env, "PWD", cwd);
}


char	*create_new_var(const char *var, const char *value)
{
	size_t	var_len;
	char	*new_var;

	var_len = ft_strlen(var);
	new_var = (char *)malloc(var_len + ft_strlen(value) + 2);
	if (!new_var)
		exit(EXIT_FAILURE);
	ft_string_cpy(new_var, var);
	ft_strcat(new_var, "=", 1);
	ft_strcat(new_var, value, ft_strlen(value));
	return (new_var);
}

char	**alloc_new_env(size_t i, char *new_var, char **env)
{
	char	**new_env;

	new_env = realloc(env, sizeof(char *) * (i + 2));
	if (!new_env)
	{
		free(new_var);
		exit(EXIT_FAILURE); // Code de sortie !!
	}
	new_env[i] = new_var;
	new_env[i + 1] = NULL;
	return (new_env);
}

void	env_with_new_var(char **env, const char *var, const char *value)
{
	size_t	i;
	size_t	var_len;
	char	*new_var;
	char	**new_env;

	var_len = ft_strlen(var);
	i = -1;
	new_var = create_new_var(var, value);
	while (env[++i])
	{
		if (strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
		{
			free(env[i]);
			env[i] = new_var;
			return ;
		}
	}
	new_env = alloc_new_env(i, new_var, env);
	env = new_env;
	free_tab(new_env);
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

void	change_pwd_env(t_minishell *minishell, const char *cwd,
	const char *old_cwd)
{
	if (is_var_existing(minishell) == 1)
	{
		env_with_new_var(minishell->env, "PWD", cwd);
	}
	if (is_var_existing(minishell) == 2)
	{
		env_with_new_var(minishell->env, "OLDPWD", old_cwd);
	}
}

void	get_new_pwd(t_minishell *minishell, char *cmd)
{
	char	cwd[1024];
	char	old_cwd[1024];

	if (getcwd(old_cwd, sizeof(old_cwd)) == NULL)
	{
		perror("getcwd");
		return ;
	}
	if (cmd != NULL)
	{
		if (chdir(cmd) != 0)
		{
			printf("bash: cd: No such file or directory\n");
			return ;
		}
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("Can't get the new path\n");
			return ;
		}
	}
	change_pwd_env(minishell, cwd, old_cwd);
}

void	builtin_cd(t_minishell *minishell, char **cmd)
{
	char	*path;

	path = NULL;
	if (cmd[1] == NULL)
	{
		if (ft_strcmp(cmd[0], "cd") != 0)
			printf("bash: %s: No such file or directory\n", cmd[0]);
		go_back_user(minishell);
		return ;
	}
	if (cmd[2])
	{
		printf("bash: cd: too many arguments\n");
		return ;
	}
	if (check_cd_errors(cmd, minishell) == 1)
	{
		go_back_home(minishell);
		return ;
	}
	if (cmd[1] != NULL && is_relative_path(cmd) == 0)
	{
		path = relative_to_absolute_path(cmd, minishell);
		if (!path)
			return ;
	}
	get_new_pwd(minishell, path);
	free(path);
}
