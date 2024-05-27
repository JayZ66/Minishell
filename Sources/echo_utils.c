/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:59:10 by marvin            #+#    #+#             */
/*   Updated: 2024/05/24 11:59:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	manage_echo_slash(size_t slash_count, char *cmd, size_t i)
{
	size_t	to_print;
	size_t	j;

	if (cmd[i] == 'n' && slash_count > 0)
	{
		to_print = slash_count / 2;
		j = -1;
		while (++j < to_print)
			printf("\\");
		printf("n ");
		slash_count = 0;
	}
	else
	{
		j = -1;
		while (++j < slash_count)
			printf("\\");
		slash_count = 0;
		printf("%c", cmd[i]);
	}
	return (slash_count);
}

void	how_many_back_slash(char *cmd)
{
	size_t	i;
	size_t	j;
	size_t	slash_count;

	i = -1;
	slash_count = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\\')
			slash_count++;
		else
		{
			slash_count = manage_echo_slash(slash_count, cmd, i);
		}
	}
	j = -1;
	while (++j < slash_count)
		printf("\\");
}

int	echo_option(char *cmd)
{
	size_t	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_strschr(cmd, "-n") == 0)
		{
			if (cmd[i] != '-' && cmd[i] != 'n')
				return (1);
		}
		i++;
	}
	return (0);
}

size_t	count_sign(char **cmd)
{
	size_t	i;
	size_t	j;
	size_t	count_sign;

	i = 0;
	if (ft_strncmp(cmd[i], "echo", 4) == 0)
		i++;
	while (cmd[i])
	{
		j = 0;
		count_sign = 0;
		if (echo_option(cmd[i]) == 1)
			break ;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '-')
				count_sign++;
			if (count_sign > 1 || count_sign == 0)
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int	is_there_something_after_quote(char *str)
{
	int	i;
	int	something_after;

	i = 0;
	something_after = 0;
	while (str[i])
	{
		if ((str[i] != ' ' && (str[i] < 9 || str[i] > 13))
			|| ((str[i] == '\'' || str[i] == '"') && str[i + 1] == '\0'))
		{
			something_after = 1;
			return (something_after);
		}
		i++;
	}
	return (0);
}
