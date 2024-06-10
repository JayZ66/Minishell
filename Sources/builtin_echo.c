/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 20:33:23 by marvin            #+#    #+#             */
/*   Updated: 2024/04/16 20:33:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_there_something_after_n(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '-' && (cmd[i + 1] && cmd[i + 1] == 'n'))
			i += 2;
		if (cmd[i] == '\0')
			break ;
		if (cmd[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	builtin_echo(char *str, t_minishell *exit_code)
{
	char	**cmd_with_options;

	cmd_with_options = ft_split(str, ' ');
	if (cmd_with_options[1])
	{
		if (ft_strncmp(cmd_with_options[1], "-n", 2) == 0
			&& is_there_something_after_n(cmd_with_options[1]) == 0)
			handle_echo_with_n(cmd_with_options);
		else if (cmd_with_options[1]
			&& (ft_strcmp(cmd_with_options[1], "-n") != 0)
			&& (ft_strcmp(cmd_with_options[0], "-n") != 0))
			print_echo_arg(cmd_with_options, exit_code);
	}
	else if (ft_strcmp(cmd_with_options[0], "echo") != 0
		&& ft_strcmp(cmd_with_options[0], "/bin/echo") != 0)
	{
		exit_code->last_exit_status = 127;
		printf("%s: command not found\n", cmd_with_options[0]);
	}
	else
		printf("\n");
	ft_free(cmd_with_options);
}

void	handle_echo_with_n(char **cmd)
{
	size_t	i;

	i = count_sign(cmd);
	while (cmd[i])
	{
		if (cmd[i + 1] == NULL)
			printf("%s", cmd[i]);
		else
			printf("%s ", cmd[i]);
		i++;
	}
}

char	*copy_str_without_first_quote(char *source)
{
	size_t	source_length;
	size_t	j;
	size_t	i;
	char	*result;

	source_length = strlen(source);
	j = 0;
	i = -1;
	result = (char *)ft_malloc(source_length + 1);
	if (result == NULL || source == NULL)
		return (NULL);
	while (source[++i] && i < source_length)
	{
		if (((source[i] == '\'' || source[i] == '"')
				&& !(is_space(source[i - 1]))) && (!(is_space(source[i + 1]))
				&& source[i + 1] != '\0' && i != 0))
			result[j++] = source[i];
		else if ((source[i] < 9 || source[i] > 13)
			&& (source[i] != '\'' && source[i] != '"'))
			result[j++] = source[i];
	}
	result[j] = '\0';
	return (result);
}

char	*copy_string_without_char(const char *source, char exclude_char)
{
	size_t	source_length;
	size_t	j;
	size_t	i;
	char	*result;

	source_length = strlen(source);
	j = 0;
	i = 0;
	if (source == NULL)
		return (NULL);
	result = (char *)ft_malloc(source_length + 1);
	if (result == NULL)
		return (NULL);
	while (source[i] && i < source_length)
	{
		if (source[i] != exclude_char)
		{
			result[j] = source[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

/*
1. Si un simple/double quote ==> On retire
2. Si deux simple/double quote ==> On retire le premier niveau
*/
