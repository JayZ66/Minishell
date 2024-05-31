/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/31 17:21:53 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pwd_option(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
		{
			printf("bash: pwd: %s: invalid option\n", str + i);
			return (1);
		}
		if (str[i] != 'p' && str[i] != 'w' && str[i] != 'd')
		{
			printf("bash: pwd: Command '%s' not found\n", str);
			return (1);
		}
		i++;
	}
	return (0);
}

// int	built_in_or_not_builtin_second()
// {
	
// }

// Check si built_in dans mon execution => Si oui on redirige
// le résultat (dup2) et on n'envoie pas dans execve.
// Check how to manage the new env !
// Need to change the return ? unset - cd - export ??
int	builtin_or_not_builtin(char *str, t_minishell *minishell,
	t_minishell *exit_code)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(str, "pwd", 3) == 0)
			builtin_pwd(str, minishell);
	else if (ft_strncmp(str, "env", 4) == 0)
		builtin_env(minishell);
	else if (ft_strncmp(str, "exit", 4) == 0)
		builtin_exit(cmd, exit_code, minishell);
	else if (ft_strncmp(str, "unset", 5) == 0)
		builtin_unset(cmd, minishell);
	else if (ft_strncmp(str, "cd", 2) == 0)
		builtin_cd(minishell, cmd);
	else if (ft_strncmp(str, "echo", 4) == 0)
		builtin_echo(str, exit_code);
	else if (ft_strncmp(str, "export", 6) == 0)
		builtin_export(cmd, minishell);
	else
		return (free_tab(cmd), 1);
	free_tab(cmd);
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
