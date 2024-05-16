/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:55:48 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/16 17:57:34 by jeguerin         ###   ########.fr       */
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
		i++;
	}
	return (0);
}

/*
DetectBuiltInCmd
*/
// Check si built_in dans mon execution => Si oui on redirige
// le résultat (dup2) et on n'envoie pas dans execve.
// Check how to manage the new env !
// Need to change the return ? unset - cd - export ??
int	builtin_or_not_builtin(char *str, t_minishell *minishell, t_minishell *exit_code)
{
	char	**cmd;
	(void)exit_code;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(str, "pwd", 3) == 0)
	{
		if (check_pwd_option(str) == 0)
			builtin_pwd();
	}
	else if (ft_strncmp(str, "env", 4) == 0)
		builtin_env(minishell);
	else if (ft_strncmp(str, "exit", 4) == 0)
		builtin_exit(cmd, exit_code);
	else if (ft_strncmp(str, "unset", 5) == 0)
		builtin_unset(cmd, minishell);
	else if (ft_strncmp(str, "cd", 2) == 0)
		builtin_cd(minishell, cmd);
	else if (ft_strncmp(str, "echo", 4) == 0)
		builtin_echo(str, exit_code);
	else if (ft_strncmp(str, "export", 6) == 0)
		builtin_export(str, minishell);
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
	count_quotes = 0;
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

void	remove_quotes_cmd_line(t_final_token *node)
{
	while (node)
	{
		if (node->type != PIPE)
			node->content = managing_quotes(node->content);
		node = node->next;
	}
}