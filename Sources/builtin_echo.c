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

void	print_echo_arg(char **cmd_with_options, t_minishell *exit_code)
{
	size_t	i;

	i = -1;
	while (cmd_with_options[++i])
	{
		if (ft_strcmp(cmd_with_options[i], "echo") == 0)
			i++;
		if (ft_strschr(cmd_with_options[i], "$?") == 0
			|| ft_strschr(cmd_with_options[i], "$?$") == 0)
		{
			printf("%d\n", exit_code->last_exit_status);
			break ;
		}
		if (ft_strschr(cmd_with_options[i], "\\n") == 0)
		{
			how_many_back_slash(cmd_with_options[i]);
			i++;
		}
		printf("%s ", cmd_with_options[i]);
		if (cmd_with_options[i + 1] == NULL)
			printf("\n");
	}
}

void	builtin_echo(char *str, t_minishell *exit_code)
{
	char	**cmd_with_options;

	cmd_with_options = ft_split(str, ' ');
	if (cmd_with_options[1])
	{
		if ((ft_strschr(cmd_with_options[1], "-n") == 0
				|| ft_strschr(cmd_with_options[0], "-n") == 0))
			handle_echo_with_n(cmd_with_options);
		else if (cmd_with_options[1]
			&& (ft_strcmp(cmd_with_options[1], "-n") != 0)
			&& (ft_strcmp(cmd_with_options[0], "-n") != 0))
			print_echo_arg(cmd_with_options, exit_code);
	}
	else if (ft_strcmp(cmd_with_options[0], "echo") != 0)
		printf("%s: command not found\n", cmd_with_options[0]);
	else
		printf("\n");
	free_tab(cmd_with_options);
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
	result = (char *)malloc(source_length + 1);
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
	result = (char *)malloc(source_length + 1);
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
