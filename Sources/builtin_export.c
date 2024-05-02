/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:12:21 by marvin            #+#    #+#             */
/*   Updated: 2024/04/02 22:12:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
Will modify the value of the identified
var. in the environment.
*/

char	**modify_value_env(char **env, char *var, char *new_value)
{
	size_t	i;
	size_t	size_env;
	char	**new_env;

	i = -1;
	size_env = ft_size_env(env);
	new_env = (char **)malloc(sizeof(char *) * (size_env + 1));
	if (!new_env)
	{
		perror("Can't create the new env.\n");
		exit(EXIT_FAILURE);
	}
	while (env[++i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0
			&& env[i][ft_strlen(var)] == '=')
		{
			new_env[i] = copy_new_value(new_env[i], var, new_value);
			i++;
		}
		new_env[i] = ft_strdup(env[i]);
	}
	free_tab(env);
	new_env[size_env] = NULL;
	return (new_env);
}

char	*copy_new_value(char *new_env, char *var, char *new_value)
{
	size_t	new_var_len;

	new_var_len = ft_strlen(var) + ft_strlen(new_value) + 1;
	new_env = (char *)malloc(sizeof(char) * new_var_len);
	if (!new_env)
	{
		perror("Memory allocation for new var. failed\n");
		exit(EXIT_FAILURE);
	}
	new_env = ft_string_cpy(new_env, var);
	new_env = ft_strcat(new_env, new_value, ft_strlen(new_value));
	return (new_env);
}

char	**create_var_env(char **env, char *var)
{
	size_t	size_env;
	size_t	i;
	char	**new_env;

	size_env = ft_size_env(env);
	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (size_env + 2));
	if (!new_env)
	{
		perror("Can't create the new env.\n");
		exit(EXIT_FAILURE);
	}
	while (i < size_env)
	{
		new_env[i] = ft_strdup(env[i]);
		free(env[i]);
		i++;
	}
	free(env);
	new_env[size_env] = ft_strdup(var);
	new_env[size_env + 1] = NULL;
	return (new_env);
}

// void	update_env(char **env, char *var)
// {
// 	env = create_var_env(env, var);
// 	// free_tab(*env);
// 	// *env = new_env;
// 	print_tab(env);
// }

// On check, first, si la variable, que l'on souhaite
// modifier ou créer existe dans l'env. ou non.
// char	**builtin_export(char **args, char **env)
// {
// 	size_t	i;
// 	char	**new_env;

// 	i = 0;
// 	new_env = NULL;
// 	if (args[1] != NULL)
// 	{
// 		while (args[1][i])
// 		{
// 			if (args[1][i] == '=')
// 			{
// 				new_env = modify_or_create(args, env, i, new_env);
// 				return (new_env);
// 			}
// 			i++;
// 		}
// 	}
// 	else
// 	{
// 		new_env = print_env(env);
// 		return (new_env);
// 	}
// 	perror("The cmd is not the export we're expected\n");
// 	return (NULL);
// }

//Specific case : 
// char	**var_with_quotes(char *var)
// {
// 	size_t	i;
// 	char	*str;
// 	char	**var;

// 	i = 0;
// 	if (!(handle_quote_errors(var)))
// 	{
// 		perror("Problem with quotes\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	while (var[i])
// 	{
// 		if (ft_strncmp(var, "export", 6) == 0)
// 		{
// 			str = ft_substr(var, 0, 6);
// 		}
// 	}
// }

int	if_quote(char *var_env)
{
	int		quote;
	size_t	i;

	quote = 0;
	i = 0;
	while (var_env[i])
	{
		if (var_env[i] == '"' || var_env[i] == '\'')
			quote = 1;
		i++;
	}
	return (quote);
}

char	**clean_spaces(char **args)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	while (args[i])
	{
		j = 0;
		k = 0;
		if (ft_strnchr(args[i], '=') == 0)
			args[i] = args[i];
		else
		{
			while (args[i][j])
			{
				if (args[i][j] != 32)
				{
					args[i][k] = args[i][j];
					k++;
				}
				j++;
			}
			args[i][k] = '\0';
		}
		i++;
	}
	return (args);
}

int	is_something_after_equal(char *str)
{
	size_t	i;
	int		is_equal;

	i = 0;
	is_equal = 0;
	while (str[i])
	{
		if (str[i] == '=')
			is_equal = 1;
		else if (is_equal == 1 && str[i] != '\0')
			return (1);
		i++;
	}
	return (0);
}

char	**manage_quote_export(char *input)
{
	char	**args;
	// char	*str;
	size_t	i;
	
	if (ft_strnstr(input, "export", 7) != NULL)
		input += 7;
	args = ft_split(input, '"');
	i = 0;
	// str = ft_strjoin(args[0], args[1]);
	args = clean_spaces(args);
	while (args[i])
	{
		if (is_something_after_equal(args[i]) == 1)
			args[i] = args[i];
		else if (ft_strnchr(args[i], '=') != 0 && is_something_after_equal(args[i]) == 0)
			args[i] = ft_strjoin(args[i], args[i + 1]);
		i++;
	}
	args[i] = '\0';
	print_tab(args);
	return (args);
}

char	**builtin_export(char *var_env, char **env)
{
	size_t	i;
	size_t	j;
	char	**args;
	char	**new_env;

	i = 0;
	args = NULL;
	new_env = NULL;
	if (if_quote(var_env) == 1)
		args = manage_quote_export(var_env);
	if (args == NULL)
		args = ft_split(var_env, ' ');
	if (args[1] != NULL)
	{
		while (args[i])
		{
			j = 0;
			while (args[i][j])
			{
				if (args[i][j] == '=')
				{
					env = modify_or_create(args, env, i, j);
					if (args[i + 1] == NULL)
						return (env);
				}
				j++;
			}
			i++;
		}
	}
	else
	{
		new_env = print_env(env);
		return (new_env);
	}
	perror("The cmd is not the export we're expected\n");
	return (env);
}

// if (args[1][i] == '=')
// {
// 	var = ft_substr(args[1], 0, i);
// 	if (is_var_in_env(var, env) == 1)
// 	{
// 		new_env = modify_value_env(env, var, args[1] + i);
// 		free(var);
// 		return (new_env);
// 	}
// 	else
// 	{
// 		new_env = create_var_env(env, args[1]);
// 		free(var);
// 		return (new_env);
// 	}
// }

/*
1. Check s'il y a bien un argument. (nom var.)
2. Vérifier si la forme est bien 'NOM=valeur'. 
	a. OUI : on définit la var. d'env. avec la
	valeur correspondante.
	b. NON : Uniquement le nom d'une var., on
	définit (crée) cette var. avec une valeur vide.
3. Propagation : S'assurer que c'est new var. d'env.
sont propagées à tous les processus enfants. (TO SEE ?)
4. Gérer les erreurs : 
	a. Arg. incorrects.
	b. Pb lors de la définition des var. d'env.
5. Si pas d'argument : 
	a. On affiche l'environnement. (SEE la diff. avec env.)
*/
