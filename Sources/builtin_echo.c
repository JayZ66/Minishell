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

/*
Need to handle : 
- echoHola => Need to go to the exec. or to manage the error.
- echo-nHola => Same
- echo   \n hello => Need to pass le \
=> Global error management ?
- echo "          " | cat -e
=> Need to keep the space and exec the cmd line.
=> Can't work bce of split with space => to check !
- ""''echo hola""'''' que""'' tal""'' 
=> Manage quotes
- echo -n -nnn -nnnn => Si le 1er -n a plein de n fonctionne et le fait.
=> Need to do the -n & skip the others.
So the input is empty.
- echo -n -nnn hola -nnnn
=> Need to do -n, then skip the 3 n
& write hola -nnnn
- echo -nnn --------n
=> Need to do -n & print ---------n
- echo -nnn -----nn---nnnn
=> Need to do -n & to print le reste.
- echo -nnn --------nnnn
=> Need to do -n & print le reste.
- echo " $ " | cat -e
- echo ' $ ' | cat -e
Echo n'affiche pas le $ !
Gerer les quotes avant le split !
=> Garder le $
- Cf. KO.txt pour gerer la var. d'env avec echo.
*/

void    builtin_echo(char *str, t_minishell *exit_code)
{
    char    **cmd_with_options;
    // char    *cleaned_quotes;
    size_t    i;

    i = -1;
    cmd_with_options = ft_split(str, ' ');
    // while (cmd_with_options[++i])
    //     cmd_with_options[i] = managing_quotes(cmd_with_options[i]);
    // cleaned_quotes = clean_quote(str);
    // printf("quotes : %s\n", cleaned_quotes);
    // cmd_with_options = ft_split(cleaned_quotes, ' ');
    i = -1;
    if (((ft_strschr(cmd_with_options[1], "-n") == 0 || ft_strschr(cmd_with_options[0], "-n") == 0) && count_sign(cmd_with_options) > 1))
        handle_echo_with_n(cmd_with_options);
    else if (cmd_with_options[1] && (ft_strcmp(cmd_with_options[1], "-n") != 0)
        && (ft_strcmp(cmd_with_options[0], "-n") != 0))
    {
        while (cmd_with_options[++i])
        {
            if (ft_strcmp(cmd_with_options[i], "echo") == 0)
                i++;
            if (ft_strschr(cmd_with_options[i], "$?") == 0 || ft_strschr(cmd_with_options[i], "$?$") == 0)
            {
                printf("%d\n", exit_code->last_exit_status);
                break ;
            }
            printf("%s ", cmd_with_options[i]);
            if (cmd_with_options[i + 1] == NULL)
                printf("\n");
        }
    }
    // else if (ft_strcmp(cmd_with_options[1], "-n") == 0
    //     || ft_strcmp(cmd_with_options[0], "-n") == 0)
        // handle_echo_with_n(cmd_with_options);
    else
        printf("\n");
    free_tab(cmd_with_options);
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

/*
1. We need to check if -n
2. On le saut et on affiche tout le reste
3. On ne met pas de /n à la fin.
*/
void    handle_echo_with_n(char **cmd)
{
    size_t	i;

	i = count_sign(cmd);
    while (cmd[i])
    {
		// if (ft_strschr(cmd[i], "-n") == 0)
		// {
		// 	i++;
		// 	continue ;
		// }
        if (cmd[i + 1] == NULL)
            printf("%s", cmd[i]);
        else
            printf("%s ", cmd[i]);
        // fflush(stdout);
        i++;
    }
}

// char  *handle_quotes(char *cmd)
// {
//   size_t  i;
//   size_t  j;
//   size_t  z;
//   int     multiple_quotes;
//   int     first_quote;
//   char    *str;
//   size_t  str_size;

//   str_size = 0;
//   i = 0;
//   j = 0;
//   multiple_quotes = 0;
//   first_quote = 0;
//   while(cmd[i])
//   {
//     z = 0;
//     if (cmd[i] == '\'' || cmd[i] == '"') 
//     {
//       z = i + 1;
//       while (cmd[z] && cmd[z] != cmd[i])
//       {
//         if (cmd[z] == '\'' || cmd[z] == '"')
//           multiple_quotes = 1;
//          z++;
//        }
//      }
//      i++;
//   }
//   i = 0;
//   while (cmd[i])
//   {
//     if (multiple_quotes == 1)
//     {
//       if (first_quote != 1 && (cmd[i] == '\'' || cmd[i] == '"'))
//       {
//         first_quote = 1;
//         i++;
//       }
//       if (first_quote == 1 && (is_there_someting_after_quote(cmd + i) == 0))
//       {
//         str_size = ft_strlen(cmd + i) - 1;
//         str = ft_substr(cmd + i, 0, str_size);
//         return (str);
//       }
//       else if (first_quote == 1
//			&& (is_there_someting_after_quote(cmd + i) == 1))
//       {
//         str = copy_str_without_first_quote(cmd);
//         return (str);
//       }
//     }
//     else if (cmd[i] == '\'' || cmd[i] == '"')
//     {
//       j = i + 1;
//       while (cmd[j])
//       {
//         if (cmd[j] == cmd[i]
//			&& (is_there_someting_after_quote(cmd + j) == 1))
//         {
//           str = copy_string_without_char(cmd, cmd[i]);
//           return (str);
//         }
//         j++;
//       }
//     }
//     else
//     {
//       if (cmd[i] == '\'' || cmd[i] == '"')
//       {
//         i++;
//         str_size = ft_strlen(cmd + i) - 1;
//         str = ft_substr(cmd + i, 0, str_size);
//         return (str);
//       }
//     }
//     i++;
//   }
//   return (cmd);
// }

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
		// else if ((str[i] == '\'' || str[i] == '"') 
		//     && (str[i + 1] == '\'' || str[i + 1] == '"'))
		//   return (something_after = 1, something_after);
		i++;
	}
	return (0);
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
