/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:58:16 by marvin            #+#    #+#             */
/*   Updated: 2024/06/03 13:58:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_unset_errors(char **var, t_minishell *minishell)
{
	if (ft_strcmp(var[0], "unset") != 0)
	{
		minishell->last_exit_status = 127;
		printf("%s: command not found\n", var[0]);
	}
}

void	unset_variable(char **var, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	while (var[++j])
	{
		i = -1;
		while (minishell->env[++i])
		{
			if (ft_strncmp(minishell->env[i], var[j], ft_strlen(var[j])) == 0
				&& minishell->env[i][ft_strlen(var[j])] == '=')
			{
				ft_free(minishell->env[i]);
				k = i;
				while (minishell->env[k + 1])
				{
					minishell->env[k] = minishell->env[k + 1];
					k++;
				}
				minishell->env[k] = NULL;
				break ;
			}
		}
	}
}

void	builtin_unset(char **var, t_minishell *minishell)
{
	if (var[1])
		unset_variable(var, minishell);
	check_unset_errors(var, minishell);
}
