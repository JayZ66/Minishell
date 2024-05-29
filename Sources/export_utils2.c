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

char	**manage_quote_export(char *input)
{
	char	**args;
	size_t	i;

	if (ft_strnstr(input, "export", 7) != NULL)
		input += 7;
	args = ft_split(input, '"');
	i = 0;
	args = clean_spaces(args);
	while (args[i])
	{
		if (is_something_after_equal(args[i]) == 1)
			args[i] = args[i];
		else if (ft_strnchr(args[i], '=') != 0
			&& is_something_after_equal(args[i]) == 0)
			args[i] = ft_strjoin(args[i], args[i + 1]);
		i++;
	}
	args[i] = '\0';
	print_tab(args);
	return (args);
}

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

int	identifier_errors_export(char *args)
{
	size_t	i;

	i = 0;
	while (args[i] && args[i] != '=')
	{
		if (check_char_export(args[i]) == 1)
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
