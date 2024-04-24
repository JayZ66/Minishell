/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:01:08 by marvin            #+#    #+#             */
/*   Updated: 2024/04/19 12:01:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
MANAGE QUOTES
*/

int	is_there_multiple_quotes(char *cmd)
{
	size_t	i;
	size_t	z;
	int		quotes;

	i = 0;
	quotes = 0;
	while(cmd[i])
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


char	*removing_one_level_of_quote(char *cmd, char c, size_t i)
{
	size_t	j;
	char	*str;

	j = i + 1;
	while (cmd[j])
	{
		if (cmd[j] == cmd[i] && (is_there_someting_after_quote(cmd + j) == 1))
		{
			str = copy_string_without_char(cmd, cmd[i]); // In builtin_echo.c
			return (str);
		}
		j++;
	}
	return (str = NULL);
}

char	*check_initial_quote(char *cmd)
{
	size_t	i;
	size_t	str_size;
	char	*str;

	i = -1;
	str_size = 0;
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
char *check_multiple_quotes(char *cmd)
{
    size_t	i;
	size_t	str_size;
    int 	first_quote;

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
        if (first_quote == 1 && (is_something_after_quote(cmd + i) == 0))
        {
            str_size = ft_strlen(cmd + i) - 1;
            return (ft_substr(cmd + i, 0, str_size));
        }
        else if (first_quote == 1 && (is_something_after_quote(cmd + i) == 1))
            return (copy_str_without_first_quote(cmd)); 
        i++;
    }
    return (cmd);
}

char *check_quotes(char *cmd, int multiple_quotes)
{
    if (multiple_quotes == 1)
        return (check_multiple_quotes(cmd));
    else
        return (check_initial_quote(cmd));
}

char  *handle_quotes(char *cmd)
{
  int	multiple_quotes;
  char	*str;

  multiple_quotes = is_there_multiple_quotes(cmd);
  str = check_quotes(cmd, multiple_quotes);
  return (str);
}

/*
ConvertPathToAbsolute
*/
// Maybe not useful for the cmd line.
int	is_relative_path(char **cmd)
{
	size_t	i;
	size_t	is_absolute;

	is_absolute = 0;
	if (cmd[1] != NULL)
	{
		i = 0;
		while (cmd[1][i])
		{
			if (cmd[1][0] == '/' && cmd[1][1]) // Check when we put just "//"
			{
				is_absolute = 1;
				break ;
			}
			else
				break ;
			i++;
		}
	}
	return (is_absolute);
}

// TESTER SUR MAC pour les ".." et quelles est la racine
// que l'on doit protéger ? + Si ça fonctionne ou non !
char	*relative_to_absolute_path(char **cmd)
{
	char	cwd[1024];
	char	*partial_path;
	char	*final_path;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Can't get the new path\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(cmd[1], "..") == 0
		&& ft_strcmp(cwd, getenv("HOME")) == 0)
		return (perror("Can't go higher than the root\n"), NULL);
	partial_path = ft_strjoin(cwd, "/");
	final_path = ft_strjoin(partial_path, cmd[1]);
	free(partial_path);
	return (final_path);
}
/*
ReplaceEnvVars
*/
// How to replace the var. in the list ?
// Should we send the node->content ?
// How do we change the value of the node->content ?
char	*extract_var(char *str)
{
	size_t	i;
	char	*var_env;
	char	*result;

	i = 0;
	if (str[i] == '$')
	{
		i++;
		var_env = ft_substr(str + i, 0, ft_strlen(str + i));
		result = getenv(var_env);
		if (result == NULL)
			return (perror("This var. is not existing in the env.\n"),
				free(var_env), NULL);
		return (free(var_env), result);
	}
	perror("Can't get the var. of env.");
	return (NULL);
}

char	*get_the_var_of_env(t_token *node)
{
	t_token	*tmp;
	// char	*var_env;
	// char	*result;
	char	*var;
	size_t	i;

	tmp = node;
	while (tmp)
	{
		i = -1;
		while (tmp->content[++i])
		{
			while (tmp->content[i] == ' ')
				i++;
			var = extract_var(tmp->content + i);
			if (!var)
				return (NULL);
			return (var);
		}
		tmp = tmp->next;
	}
	return (perror("Can't get this var.\n"), NULL);
}

/*
DetectBuiltInCmd
*/
// Check si built_in dans mon execution => Si oui on redirige
// le résultat (dup2) et on n'envoie pas dans execve.
// Check how to manage the new env !
void	builtin_or_not_builtin(char *str, char **env)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	if (ft_strncmp(str, "pwd", 3) == 0)
		builtin_pwd(str);
	else if (ft_strncmp(str, "env", 4) == 0)
		builtin_env(env);
	else if (ft_strncmp(str, "exit", 4) == 0)
		builtin_exit(str);
	else if (ft_strncmp(str, "unset", 5) == 0)
		builtin_unset(cmd, env); // Change the return.
	else if (ft_strncmp(str, "cd", 2) == 0)
		builtin_cd(env, cmd); // Change the return.
	else if (ft_strncmp(str, "echo", 4) == 0)
		builtin_echo(str);
	else if (ft_strncmp(str, "export", 6) == 0)
		builtin_export(cmd, env); // Change the return.
}

/*
Expanser
*/


// char	*check_quotes(char *cmd, int multiple_quotes)
// {
// 	size_t	j;
// 	size_t	i;
// 	int		first_quote;
// 	char	*str;
// 	int		str_size;

// 	i = 0;
// 	first_quote = 0;
// 	while (cmd[i])
// 	{
// 		if (multiple_quotes == 1)
// 		{
// 			if (first_quote != 1 && (cmd[i] == '\'' || cmd[i] == '"'))
// 			{
// 				first_quote = 1;
// 				i++;
// 			}
// 			if (first_quote == 1 && (is_there_someting_after_quote(cmd + i) == 0)) // In builtin_echo.c
// 			{
// 				str_size = ft_strlen(cmd + i) - 1;
// 				str = ft_substr(cmd + i, 0, str_size);
// 				return (str);
// 			}
// 			else if (first_quote == 1 && (is_there_someting_after_quote(cmd + i) == 1))
// 			{
// 				str = copy_str_without_first_quote(cmd); // In builtin_echo.c
// 				return (str);
// 			}
// 		}
// 		else if (cmd[i] == '\'' || cmd[i] == '"')
// 		{
// 			j = i + 1;
// 			while (cmd[j])
// 			{
// 				if (cmd[j] == cmd[i] && (is_there_someting_after_quote(cmd + j) == 1))
// 				{
// 				str = copy_string_without_char(cmd, cmd[i]); // In builtin_echo.c
// 				return (str);
// 				}
// 				j++;
// 			}
// 		}
// 		else
// 		{
// 			if (cmd[i] == '\'' || cmd[i] == '"')
// 			{
// 				i++;
// 				str_size = ft_strlen(cmd + i) - 1;
// 				str = ft_substr(cmd + i, 0, str_size);
// 				return (str);
// 			}
// 		}
// 		i++;
// 	}
//   return (cmd);
// }