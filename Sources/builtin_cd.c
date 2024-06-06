/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:04:14 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/06 15:20:37 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*create_new_var(const char *var, const char *value)
{
	size_t	var_len;
	char	*new_var;

	var_len = ft_strlen(var);
	new_var = (char *)ft_malloc(var_len + ft_strlen(value) + 2);
	if (!new_var)
		exit(EXIT_FAILURE);
	ft_string_cpy(new_var, var);
	ft_strcat(new_var, "=", 1);
	ft_strcat(new_var, value, ft_strlen(value));
	return (new_var);
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
			ft_free(env[i]);
			env[i] = new_var;
			return ;
		}
	}
	new_env = alloc_new_env(i, new_var, env);
	env = new_env;
	ft_free(new_env);
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
	if (check_cd(cmd, minishell) == 1)
		return ;
	if (cmd[1] != NULL && is_relative_path(cmd) == 0)
	{
		path = relative_to_absolute_path(cmd, minishell);
		if (!path)
			return ;
	}
	get_new_pwd(minishell, path);
	ft_free(path);
}
