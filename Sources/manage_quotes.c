/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 10:51:22 by jeguerin          #+#    #+#             */
/*   Updated: 2024/05/12 17:02:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *clean_quote(char *input)
{
    int i;
    int tmp;

    i = 0;
    tmp = 0;
    while (input[i])
    {
        if (input[i] == '"' && ft_strnchr(input + i + 1, '"'))
        {
            tmp = i + 1 + ft_strnchr(input + i + 1, '"');
            input = ft_strjoin(ft_strjoin(ft_substr(input, 0, i), ft_substr(input, i + 1, ft_strnchr(input + i + 1, '"'))),
            ft_substr(input + 1, ft_strnchr(input + i + 1, '"') + i + 1, ft_strlen(input)));
            i = tmp - 2;
        }
        else if (input[i] == 39 && ft_strnchr(input + i + 1, 39))
        {
            tmp = i + 1 + ft_strnchr(input + i + 1, 39);
            input = ft_strjoin(ft_strjoin(ft_substr(input, 0, i), ft_substr(input, i + 1, ft_strnchr(input + i + 1, 39))),
            ft_substr(input + 1, ft_strnchr(input + i + 1, 39) + i + 1, ft_strlen(input)));
            i = tmp - 2;
        }
        i++;
    }
    return (input);
}

char	*manage_double_quotes(char *input, int i)
{
	char	*prefix;
	char	*quoted_content;
	char	*suffix;

	prefix = ft_substr(input, 0, i);
	quoted_content = ft_substr(input, i + 1,
			ft_strnchr(input + i + 1, '"'));
	suffix = ft_substr(input + 1, ft_strnchr(input + i + 1, '"')
			+ i + 1, ft_strlen(input));
	input = ft_strjoin(ft_strjoin(prefix, quoted_content), suffix);
	return (input);
}

char	*manage_simple_quotes(char *input, int i)
{
	char	*prefix;
	char	*quoted_content;
	char	*suffix;

	prefix = ft_substr(input, 0, i);
	quoted_content = ft_substr(input, i + 1,
			ft_strnchr(input + i + 1, 39));
	suffix = ft_substr(input + 1, ft_strnchr(input + i + 1, 39)
			+ i + 1, ft_strlen(input));
	input = ft_strjoin(ft_strjoin(prefix, quoted_content), suffix);
	return (input);
}

char	*managing_quotes(char *input)
{
	int		i;
	int		tmp;

	i = 0;
	handle_quote_errors(input);
	while (input[i])
	{
		if (input[i] == '"')
		{
			tmp = i + 1 + ft_strnchr(input + i + 1, '"');
			input = manage_double_quotes(input, i);
			i = tmp - 2;
		}
		else if (input[i] == '\'')
		{
			tmp = i + 1 + ft_strnchr(input + i + 1, '\'');
			input = manage_simple_quotes(input, i);
			i = tmp - 2;
		}
		i++;
	}
	return (input);
}

// char	*managing_quotes(char *input)
// {
//     int i;
//     int tmp;

//     i = 0;
//     tmp = 0;
//     while (input[i])
//     {
//         if (input[i] == '"' && ft_strnchr(input + i + 1, '"'))
//         {
//             tmp = i + 1 + ft_strnchr(input + i + 1, '"');
//             input = ft_strjoin(ft_strjoin(ft_substr(input, 0, i), ft_substr(input, i + 1, ft_strnchr(input + i + 1, '"'))),
//             ft_substr(input + 1, ft_strnchr(input + i + 1, '"') + i + 1, ft_strlen(input)));
//             i = tmp - 2;
//         }
//         else if (input[i] == 39 && ft_strnchr(input + i + 1, 39))
//         {
//             tmp = i + 1 + ft_strnchr(input + i + 1, 39);
//             input = ft_strjoin(ft_strjoin(ft_substr(input, 0, i), ft_substr(input, i + 1, ft_strnchr(input + i + 1, 39))),
//             ft_substr(input + 1, ft_strnchr(input + i + 1, 39) + i + 1, ft_strlen(input)));
//             i = tmp - 2;
//         }
//         i++;
//     }
//     return (input);
// }

// int	main()
// {
// 	char	*str;
// 	char	*result;

// 	// str = "''''\"Salut\"'''' \"tu\" 'vas' \"''bien''\"";
// 	// str = "'\"'\"'\"OK\"'\"'\"'";
// 	// str = """""OK''''";
// 	// str = "\"'\"'\"'cat'\"'\"'\"";
// 	// str = "''''OUI''''";
// 	// str = "'\"OK\"'";
// 	str =  "MY_VAR=\"value with spaces\"";
// 	result = managing_quotes(str);
// 	// result = handle_quotes(str);
// 	printf("Clean string : %s\n", result);
// 	return(0);
// }

char	*check_initial_quote(char *cmd)
{
	size_t	i;
	size_t	str_size;
	char	*str;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			str = removing_one_level_of_quote(cmd, cmd[i], i);
			if (str != NULL)
				return (str);
		}
		else
		{
			if (cmd[i] == '\'' || cmd[i] == '"')
			{
				i++;
				str_size = ft_strlen(cmd + i) - 1;
				str = ft_substr(cmd + i, 0, str_size);
				return (str);
			}
		}
	}
	return (cmd);
}

// Check for multiple quotes and process accordingly
char	*check_multiple_quotes(char *cmd)
{
	size_t	i;
	size_t	str_size;
	int		first_quote;

	i = 0;
	first_quote = 0;
	str_size = 0;
	while (cmd[i])
	{
		if (first_quote != 1 && (cmd[i] == '\'' || cmd[i] == '"'))
		{
			first_quote = 1;
			i++;
		}
		if (first_quote == 1 && (is_there_something_after_quote(cmd + i) == 0))
		{
			str_size = ft_strlen(cmd + i) - 1;
			return (ft_substr(cmd + i, 0, str_size));
		}
		else if (first_quote == 1
			&& (is_there_something_after_quote(cmd + i) == 1))
			return (copy_str_without_first_quote(cmd));
		i++;
	}
	return (cmd);
}

// Gérer si premier quote et dernier sont les mêmes & si mêmes types.
// int	handle_type_of_quotes(char *cmd)
// {
// 	size_t	i;
// 	char	first_quote;
// 	int		count_pair_of_quotes;

// 	i = 0;
// 	while (cmd[i])
// 	{
// 		if ((cmd[i] == '\'' || cmd[i] == '"') && first_quote == NULL)
// 		{
// 			first_quote = cmd[i];
// 			i++;
// 		}
// 		if (cmd[i] == first_quote)
// 		{
// 			count_pair_of_quotes++;
// 			first_quote = NULL;
// 		}
// 		i++;
// 	}
// 	return (count_pair_of_quotes);
// }

/*
Si multiple_quotes : check si un nb pair de quotes
puis check si same au début et à la fin.
*/

char	*check_quotes(char *cmd, int multiple_quotes)
{
	if (multiple_quotes == 1)
		return (check_multiple_quotes(cmd));
	else
		return (check_initial_quote(cmd));
}

char	*handle_quotes(char *cmd)
{
	int		multiple_quotes;
	int		pair_of_quotes;
	char	*str;

	multiple_quotes = is_there_multiple_quotes(cmd);
	pair_of_quotes = handle_quote_errors(cmd);
	if (pair_of_quotes == 0)
		str = check_quotes(cmd, multiple_quotes);
	return (str);
}
