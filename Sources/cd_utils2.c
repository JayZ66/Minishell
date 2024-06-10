/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:54:37 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 13:54:37 by marvin           ###   ########.fr       */
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
		return ;
	}
	if (chdir("/") != 0)
	{
		perror("Can't change directory\n");
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Can't get the new path\n");
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
		return ;
	}
	if (chdir("/home/jeguerin/") != 0)
	{
		perror("Can't change directory\n");
		return ;
	}
	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Can't get the new path\n");
		return ;
	}
	env_with_new_var(minishell->env, "OLDPWD", old_cwd);
	env_with_new_var(minishell->env, "PWD", cwd);
}

int	check_cd(char **cmd, t_minishell *minishell)
{
	if (cmd[2])
	{
		printf("bash: cd: too many arguments\n");
		return (1);
	}
	if (check_cd_errors(cmd, minishell) == 1)
	{
		go_back_home(minishell);
		return (1);
	}
	return (0);
}
