/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:47:14 by marvin            #+#    #+#             */
/*   Updated: 2024/05/24 11:47:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_slash(char *cmd)
{
	size_t	i;
	int		count_slash;

	i = 0;
	count_slash = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			count_slash++;
		i++;
	}
	if (count_slash == 2)
	{
		ft_putstr_fd("//\n", 1);
		return (1);
	}
	else if (count_slash > 2 || count_slash == 1)
	{
		ft_putstr_fd("/\n", 1);
		return (1);
	}
	return (0);
}

int	cd_errors(char **cmd, size_t i, size_t j, t_minishell *minishell)
{
	if (cmd[i][j + 1] && ft_isalpha(cmd[i][j]) == 1
		&& (cmd[i][j + 1] == '.' || cmd[i][j + 1] == '?'))
		return (printf("Command '%s' not found\n", cmd[i]), 1);
	else if (cmd[i][j + 1] && (cmd[i][j] == '.'
		&& cmd[i][j + 1] == '/'))
		return (1);
	else if (cmd[1][j] == '/')
		if (check_slash(cmd[i]) == 1)
			return (go_back_home(minishell), 1);
	return (0);
}

int	check_cd_errors(char **cmd, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	int		one_point;

	i = -1;
	one_point = 0;
	while (cmd[++i])
	{
		j = -1;
		while (cmd[i][++j])
		{
			if (cd_errors(cmd, i, j, minishell) == 1)
				return (1);
			else if (cmd[1] && (cmd[1][j] == '.' || cmd[i][j] == '/'))
				one_point++;
		}
	}
	if (one_point == 2)
		return (1);
	return (0);
}
