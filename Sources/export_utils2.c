/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 12:34:35 by marvin            #+#    #+#             */
/*   Updated: 2024/05/24 12:34:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_char_unset(char c)
{
	if ((c >= 33 && c <= 35) || (c >= 37 && c <= 47) || (c >= 58 && c <= 64)
		|| (c >= 91 && c <= 94) || c == 96 || (c >= 123 && c <= 126))
		return (1);
	else
		return (0);
}

int	check_char_export(char c)
{
	if ((c >= 33 && c <= 35) || (c >= 37 && c <= 47) || (c >= 58 && c <= 59)
		|| c == 64 || (c >= 91 && c <= 94) || c == 96 || (c >= 123 && c <= 126))
		return (1);
	else
		return (0);
}

int	is_there_equal(char *args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	identifier_errors_export(char *args)
{
	size_t	i;

	i = 0;
	while (args[i] && args[i] != '=')
	{
		if (args[i] == '=' || is_there_equal(args) == 0)
			break ;
		else if (check_char_export(args[i]) == 1)
		{
			printf("bash: export: '%s': not a valid identifier\n", args);
			return (1);
		}
		else if (ft_isalpha(args[0]) == 0)
		{
			printf("bash: export: '%s': not a valid identifier\n", args);
			return (1);
		}
		i++;
	}
	if (args[i] == '=' && (i == 0 || (args[i - 1] >= 9 && args[i - 1] <= 13)))
		return (printf("bash: export: '%s': not a valid identifier\n",
				args), 1);
	return (0);
}

int	is_there_something_after_equal(const char *var, t_minishell *minishell)
{
	size_t	i;

	(void)minishell;
	i = 0;
	while (var[i])
	{
		if (var[i] == '=' && var[i + 1] != '\0')
			return (1);
		i++;
	}
	return (0);
}
