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

char *managing_quotes(char *input)
{
    int i;
    int tmp;
	char	*prefix;
	char	*quoted_content;
	char	*suffix;

	i = 0;
	tmp = 0;
    while (input[i])
    {
        if (input[i] == '"' && ft_strnchr(input + i + 1, '"'))
        {
            // Trouver l'indice du prochain guillemet fermant
            tmp = i + 1 + ft_strnchr(input + i + 1, '"');
            // Extraire la partie avant le guillemet ouvrant
            prefix = ft_substr(input, 0, i);
            // Extraire la partie entre les guillemets
            quoted_content = ft_substr(input, i + 1, ft_strnchr(input + i + 1, '"'));
            // Extraire la partie après le guillemet fermant
            suffix = ft_substr(input + 1, ft_strnchr(input + i + 1, '"') + i + 1, ft_strlen(input));
            // Concaténer les parties sans les guillemets
            input = ft_strjoin(ft_strjoin(prefix, quoted_content), suffix);
            // Mettre à jour l'indice pour passer le contenu entre guillemets
            i = tmp - 2;
        }
        else if (input[i] == 39 && ft_strnchr(input + i + 1, 39))
        {
            // Même procédure que ci-dessus pour les apostrophes (single quotes)
            tmp = i + 1 + ft_strnchr(input + i + 1, 39);
            prefix = ft_substr(input, 0, i);
            quoted_content = ft_substr(input, i + 1, ft_strnchr(input + i + 1, 39));
            suffix = ft_substr(input + 1, ft_strnchr(input + i + 1, 39) + i + 1, ft_strlen(input));
            input = ft_strjoin(ft_strjoin(prefix, quoted_content), suffix);
            i = tmp - 2;
        }
        i++;
    }
    return (input);
}


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
		if (cmd[j] == c && (is_there_something_after_quote(cmd + j) == 1))
		{
			str = copy_string_without_char(cmd, c); // In builtin_echo.c
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
        if (first_quote == 1 && (is_there_something_after_quote(cmd + i) == 0))
        {
            str_size = ft_strlen(cmd + i) - 1;
            return (ft_substr(cmd + i, 0, str_size));
        }
        else if (first_quote == 1 && (is_there_something_after_quote(cmd + i) == 1))
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


// To manage if quotes are by pair.
// To manage if there is the same quote at the beginning & the end.
int	handle_quote_errors(char *cmd)
{
	size_t	i;
	int		count_quotes;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
			count_quotes++;
		i++;
	}
	if (count_quotes % 2 != 0)
	{
		perror("Quote is not closed\n");
		exit(EXIT_FAILURE);
	}
	return (0);
}
/*
Si multiple_quotes : check si un nb pair de quotes
puis check si same au début et à la fin.
*/

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
  int	pair_of_quotes;
  char	*str;

  multiple_quotes = is_there_multiple_quotes(cmd);
  pair_of_quotes = handle_quote_errors(cmd);
  if (pair_of_quotes == 0)
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
// Nécessaire pour les built-ins => BEST to run.
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

int	check_var(t_token *node)
{
	t_token	*tmp;
	size_t	i;
	int		is_var_env;
	int		is_second_quote;

	tmp = node;
	while (tmp)
	{
		i = -1;
		while(tmp->content[++i])
		{
			if (tmp->content[i] == '"')
			{
				while (tmp->content[i])
				{
					if (tmp->content[i] == '$')
						is_var_env = 1;
					if (tmp->content[i] == '"')
						is_second_quote = 1;
					if ((is_var_env == 1) && (is_second_quote == 1))
						return (0); 
					i++;
				}
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*get_the_var_of_env(t_token *node)
{
	t_token	*tmp;
	// char	*var_env;
	// char	*result;
	char	*var;
	size_t	i;

	tmp = node;
	if (check_var(node) == 1) // CHECK IF WE ALWAYS NEED QUOTES TO GET VAR ENV.
	{
		perror("Can't get var. of env bce of quotes\n");
		exit(EXIT_FAILURE);
	}
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
int	builtin_or_not_builtin(char *str, char **env)
{
	char	**cmd;

	cmd = ft_split(str, ' ');
	// print_new_env(env);
	if (ft_strncmp(str, "pwd", 3) == 0)
		builtin_pwd(str);
	else if (ft_strncmp(str, "env", 4) == 0)
		builtin_env(env);
	else if (ft_strncmp(str, "exit", 4) == 0)
		builtin_exit(cmd);
	else if (ft_strncmp(str, "unset", 5) == 0)
	{
		env = builtin_unset(cmd, env); // Change the return.
		if (env == NULL)
		 {
			perror("The var. can't be unset\n");
			exit(EXIT_FAILURE);
		 }
	}
	else if (ft_strncmp(str, "cd", 2) == 0)
		env = builtin_cd(env, cmd); // Change the return.
	else if (ft_strncmp(str, "echo", 4) == 0)
		builtin_echo(str);
	else if (ft_strncmp(str, "export", 6) == 0)
		env = builtin_export(cmd, env); // Change the return.
	else
		return (1);
	// print_new_env(env);
	return (0);
}

int	is_built_in(char *str)
{
	if (ft_strncmp(str, "pwd", 3) == 0)
		return (0);
	else if (ft_strncmp(str, "env", 4) == 0)
		return (0);
	else if (ft_strncmp(str, "exit", 4) == 0)
		return (0);
	else if (ft_strncmp(str, "unset", 5) == 0)
		return (0);
	else if (ft_strncmp(str, "cd", 2) == 0)
		return (0);
	else if (ft_strncmp(str, "echo", 4) == 0)
		return (0);
	else if (ft_strncmp(str, "export", 6) == 0)
		return (0);
	else
		return (1);
}

/*
Expanser
*/

// int main()
// {
//   char  *str;

// //   str = "echo """"pourquoi'''' \"''toi''\"";
// //   str = "echo '\"""pourquoi\"""' \"''toi''\"";
//   // str = "echo";
//   // echo(str);
//   str = "echo -n \"""cat'''' \"'cat'\" 'cat'";
// //   str = "echo '-n' 'cat' cat cat";
//   // echo(str);
// //   str = "echo cat cat \"''''cat''''\"";
//   // echo(str);
// //   str = "echo \"''''Hello' 'World''''\' \"'''cat'''\" cat";
// //   str = "echo cat";
// //   builtin_echo(str);
// // str = "\"''cat\"'' ok";
// //   str = clean_quote(str);
//   str = handle_quotes(str);
//   printf("new_str : %s\n", str);
//   return (0);
// }

/*
GESTION DES GUILLEMETS : 
- Sans guillemets : echo hello world
La commande est interprétée comme trois tokens distincts : echo, Hello, World.
- Avec simple quotes : echo 'Hello World'
La commande est interprétée comme deux tokens : echo et Hello World.
- Avec double quotes : echo "Hello World"
La commande est également interprétée comme deux tokens : echo et Hello World.
*/
