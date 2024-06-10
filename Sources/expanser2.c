/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/10 15:43:04 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pwd_option(char *str, t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			minishell->last_exit_status = 2;
			printf("bash: pwd: %s: invalid option\n", str + i);
			return (1);
		}
		else if (ft_strncmp(str, "pwd", 3) != 0)
		{
			minishell->last_exit_status = 127;
			printf("bash: pwd: Command '%s' not found\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

int	builtin_or_not_builtin(char *str, t_minishell *minishell)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(str, "pwd", 3) == 0)
		builtin_pwd(str, minishell);
	else if (ft_strncmp(str, "env", 4) == 0)
		builtin_env(minishell);
	else if (ft_strncmp(str, "exit", 4) == 0)
		builtin_exit(cmd, minishell);
	else if (ft_strncmp(str, "unset", 5) == 0)
		builtin_unset(cmd, minishell);
	else if (ft_strncmp(str, "cd", 2) == 0)
		builtin_cd(minishell, cmd);
	else if (ft_strncmp(str, "echo", 4) == 0)
		builtin_echo(str, minishell);
	else if (ft_strncmp(str, "export", 6) == 0)
		builtin_export(cmd, minishell);
	else
		return (ft_free(cmd), 1);
	return (0);
}

int	is_built_in(char *str)
{
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (0);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (0);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (0);
	else
		return (1);
}
