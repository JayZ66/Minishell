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

// 1. Trouver l'indice du prochain guillemet fermant
// 2. Extraire la partie avant le guillemet ouvrant
// 3. Extraire la partie entre les guillemets
// 4. Extraire la partie après le guillemet fermant
// 5. Concaténer les parties sans les guillemets
// 6. Mettre à jour l'indice pour passer le contenu entre guillemets

/*
ConvertPathToAbsolute
*/

int	is_absolute_path(char **cmd)
{
	size_t	i;
	size_t	is_absolute;

	is_absolute = 0;
	i = 0;
	while (cmd[0][i])
	{
		if (cmd[0][0] == '/' && cmd[0][1])
		{
			is_absolute = 1;
			break ;
		}
		else
			break ;
		i++;
	}
	return (is_absolute);
}

// Maybe not useful for the cmd line.
// TO CHECK : when we put just "//"
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
			if (cmd[1][0] == '/' && cmd[1][1])
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
char	*relative_to_absolute_path(char **cmd, t_minishell *minishell)
{
	char	cwd[1024];
	char	*partial_path;
	char	*final_path;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror("Can't get the new path\n");
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(cmd[1], "..") == 0 && ft_strcmp(cwd, "/") == 0)
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

int	check_var(t_final_token *node)
{
	t_final_token	*tmp;
	size_t	i;

	tmp = node;
	while (tmp)
	{
		i = -1;
		while (tmp->content[++i])
		{
			if (tmp->content[i] == '"')
			{
				while (tmp->content[i])
				{
					if (is_var_env(tmp->content[i]) == 0)
						return (0);
					i++;
				}
			}
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*get_the_var_of_env(t_final_token *node, t_minishell *minishell)
{
	t_final_token	*tmp;
	char	*var;
	size_t	i;

	tmp = node;
	if (check_var(node) == 1)
	{
		perror("Can't get var. of env bce of quotes\n");
		minishell->last_exit_status = EXIT_FAILURE;
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
