/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/04/30 10:57:54 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
DetectBuiltInCmd
*/
// Check si built_in dans mon execution => Si oui on redirige
// le résultat (dup2) et on n'envoie pas dans execve.
// Check how to manage the new env !
// Need to change the return ? unset - cd - export ??
int	builtin_or_not_builtin(char *str, char **env)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(str, "pwd", 3) == 0)
		builtin_pwd();
	else if (ft_strncmp(str, "env", 4) == 0)
		builtin_env(env);
	else if (ft_strncmp(str, "exit", 4) == 0)
		builtin_exit(cmd);
	else if (ft_strncmp(str, "unset", 5) == 0)
	{
		env = builtin_unset(cmd, env);
		if (env == NULL)
			exit(EXIT_FAILURE);
	}
	else if (ft_strncmp(str, "cd", 2) == 0)
		env = builtin_cd(env, cmd);
	else if (ft_strncmp(str, "echo", 4) == 0)
		builtin_echo(str);
	else if (ft_strncmp(str, "export", 6) == 0)
		env = builtin_export(cmd, env);
	else
		return (1);
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

int	is_there_multiple_quotes(char *cmd)
{
	size_t	i;
	size_t	z;
	int		quotes;

	i = 0;
	quotes = 0;
	while (cmd[i])
	{
		z = 0;
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			z = i + 1;
			while (cmd[z] && cmd[z] != cmd[i])
			{
				if (cmd[z] == '\'' || cmd[z] == '"')
				{
					quotes = 1;
					return (quotes);
				}
				z++;
			}
		}
		i++;
	}
	return (quotes);
}

// To manage if quotes are by pair.
// To manage if there is the same quote at the beginning & the end.
int	handle_quote_errors(char *cmd)
{
	size_t	i;
	int		count_quotes;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			count_quotes++;
		i++;
	}
	if (count_quotes % 2 != 0)
	{
		perror("Quote is not closed\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}

char	*removing_one_level_of_quote(char *cmd, char c, size_t i)
{
	size_t	j;
	char	*str;

	j = i + 1;
	while (cmd[j])
	{
		if (cmd[j] == c && (is_there_something_after_quote(cmd + j) == 1))
		{
			str = copy_string_without_char(cmd, c);
			return (str);
		}
		j++;
	}
	return (str = NULL);
}
