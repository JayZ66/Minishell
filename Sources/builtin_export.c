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

// char	**modify_value_env(t_minishell *minishell, char *var, char *new_value)
// {
// 	size_t	i;
// 	size_t	size_env;
// 	char	**new_env;

// 	i = -1;
// 	size_env = ft_size_env(minishell->env);
// 	new_env = (char **)malloc(sizeof(char *) * (size_env + 1));
// 	if (!new_env)
// 	{
// 		perror("Can't create the new env.\n");
// 		minishell->last_exit_status = EXIT_FAILURE;
// 		exit(EXIT_FAILURE);
// 	}
// 	while (minishell->env[++i])
// 	{
// 		if (ft_strncmp(minishell->env[i], var, ft_strlen(var)) == 0
// 			&& minishell->env[i][ft_strlen(var)] == '=')
// 		{
// 			new_env[i] = copy_new_value(new_env[i], var, new_value, minishell);
// 			i++;
// 		}
// 		new_env[i] = ft_strdup(minishell->env[i]);
// 		// free(minishell->env[i]);
// 	}
// 	// free_tab(env);
// 	new_env[size_env] = NULL;
// 	return (new_env);
// }

// char	**modify_value_env(t_minishell *minishell, char *var, char *new_value)
// {
// 	size_t	i;
// 	size_t	j;
// 	size_t	size_env;
// 	char	**new_env;

// 	i = -1;
// 	size_env = ft_size_env(minishell->env);
// 	new_env = (char **)malloc(sizeof(char *) * (size_env + 1));
// 	if (!new_env)
// 	{
// 		perror("Can't create the new env.\n");
// 		minishell->last_exit_status = EXIT_FAILURE;
// 		exit(EXIT_FAILURE);
// 	}
// 	while (minishell->env[++i])
// 	{
// 		j = 0;
// 		while (minishell->env[i][j] && var[j] && minishell->env[i][j] == var[j])
//             j++;
//         if (var[j] == '\0' && minishell->env[i][j - 1] == '=')
// 			new_env[i] = copy_new_value(new_env[i], var, new_value, minishell);
// 		else
// 		{
// 			new_env[i] = ft_strdup(minishell->env[i]);
// 			free(minishell->env[i]);
// 		}
// 	}
// 	// free_tab(minishell->env);
// 	new_env[i] = NULL;
// 	return (new_env);
// }

void modify_value_env(char ***env, const char *var, const char *value, t_minishell *minishell)
{
    size_t i = 0;
	size_t	j;
    // size_t var_len = strlen(var);

    while ((*env)[i]) 
	{
        j = 0;
		while ((*env)[i][j] && var[j] && (*env)[i][j] == var[j])
            j++;
        if (var[j] == '\0' && (*env)[i][j - 1] == '=')
		{
			printf("OK C'EST BON !");
            char *new_entry = copy_new_value(var, value, minishell);
            free((*env)[i]);
            (*env)[i] = new_entry;
            printf("Modified variable: %s\n", (*env)[i]); // Debugging output
            return;
        }
        i++;
    }
}

char *copy_new_value(const char *var, const char *new_value, t_minishell *minishell) 
{
    size_t new_var_len;
	char *new_env;

	new_var_len = ft_strlen(var) + 1 + ft_strlen(new_value);
	new_env = (char *)malloc(new_var_len + 1);
    if (!new_env) 
	{
        perror("Memory allocation for new var. failed");
		minishell->last_exit_status = EXIT_FAILURE;
        exit(EXIT_FAILURE);
    }
    ft_string_cpy(new_env, var);
    ft_strcat(new_env, new_value, ft_strlen(new_value));
    return (new_env);
}

char	*check_value(char *var)
{
	size_t	i;

	i = 0;
	while (var[i])
	{
		if (var[i] == '!')
		{
			printf("bash: %s: event not found\n", var + i);
			return (ft_substr(var, 0, i));
		}
		else if (var[i] == ';')
		{
			printf("bash: %s: command not found\n", var + i);
			return (ft_substr(var, 0, i));
		}
		i++;
	}
	return (var);
}

// char	**create_var_env(t_minishell *minishell, char *var)
// {
// 	size_t	size_env;
// 	size_t	i;
// 	char	**new_env;

// 	size_env = ft_size_env(minishell->env);
// 	i = 0;
// 	new_env = (char **)malloc(sizeof(char *) * (size_env + 2));
// 	if (!new_env)
// 	{
// 		perror("Can't create the new env.\n");
// 		minishell->last_exit_status = EXIT_FAILURE;
// 		exit(EXIT_FAILURE);
// 	}
// 	while (i < size_env)
// 	{
// 		new_env[i] = ft_strdup(minishell->env[i]);
// 		free(minishell->env[i]);
// 		i++;
// 	}
// 	// free var ?
// 	// new_var = check_value(var);
// 	new_env[size_env] = ft_strdup(var);
// 	new_env[size_env + 1] = NULL;
// 	return (new_env);
// }

char	**create_var_env(t_minishell *minishell, char *var)
{
	size_t	size_env;
	size_t	i;
	char	**new_env;

	// Calculer la taille de l'environnement existant
	size_env = ft_size_env(minishell->env);

	// Allouer de la mémoire pour le nouvel environnement
	new_env = (char **)malloc(sizeof(char *) * (size_env + 2));
	if (!new_env)
	{
		perror("Can't create the new env.\n");
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}

	// Copier les anciennes variables d'environnement
	for (i = 0; i < size_env; i++)
	{
		new_env[i] = ft_strdup(minishell->env[i]);
		if (!new_env[i])
		{
			// Gérer l'échec de l'allocation de mémoire
			perror("Can't copy environment variable.\n");
			// Libérer la mémoire déjà allouée
			for (size_t j = 0; j < i; j++)
				free(new_env[j]);
			free(new_env);
			minishell->last_exit_status = EXIT_FAILURE;
			exit(EXIT_FAILURE);
		}
	}

	// Ajouter la nouvelle variable à la fin du nouvel environnement
	new_env[size_env] = ft_strdup(var);
	if (!new_env[size_env])
	{
		// Gérer l'échec de l'allocation de mémoire
		perror("Can't copy new environment variable.\n");
		// Libérer la mémoire déjà allouée
		for (i = 0; i < size_env; i++)
			free(new_env[i]);
		free(new_env);
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}

	// Terminer le nouvel environnement par NULL
	new_env[size_env + 1] = NULL;

	// Libérer l'ancien environnement
	free_tab(minishell->env);

	// Retourner le nouvel environnement
	return new_env;
}
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

char	**split_cmd(char *var_env)
{
	char	**args;

	args = NULL;
	// if (if_quote(var_env) == 1)
	// 	args = manage_quote_export(var_env);
	// else
	args = ft_split(var_env, ' ');
	return (args);
}

void	print_export_env(t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i + 1])
	{
		printf("declare -x %s\n", minishell->env[i]);
		i++;
	}
	return ;
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

int	identifier_errors_unset(char *args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (check_char_unset(args[i]) == 1)
		{
			printf("bash: export: '%s': not a valid identifier\n", args);
			return (1);
		}
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
		if (ft_isalpha(args[0]) == 0)
		{
			printf("bash: export: '%s': not a valid identifier\n", args);
			return (1);
		}
		else if (check_char_export(args[i]) == 1)
		{
			printf("bash: export: '%s': not a valid identifier\n", args);
			return (1);
		}
		i++;
	}
	if (args[i] == '=' && ((!args[i - 1]) || (args[i - 1] >= 9 && args[i - 1] <= 13)))
	{
		printf("bash: export: '%s': not a valid identifier\n", args);
		return (1);
	}
	return (0);
}

// exportOK=OK => Rien (continue)

void	builtin_export(char **args, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	// char	**args;

	i = 0;
	// args = ft_split(var_env, ' ');
	if (args[1] != NULL)
	{
		while (args[++i])
		{
			j = 0;
			if (identifier_errors_export(args[i]) == 1)
			{
				if (args[i + 1] == NULL)
					break ;
				i++;
			}
			while (args[i][j])
			{
				if (args[i][j] == '=')
				{
					modify_or_create(args, minishell, i, j);
					if (args[i + 1] == NULL)
					{
						// free_tab(args); // Why invalid free ?
						break ;
					}
				}
				j++;
			}
		}
	}
	else if (ft_strcmp(args[0], "export") != 0)
		return ;
	else
	{
		print_export_env(minishell);
		// free_tab(args);
	}
	// printf("bash: export: '%s': not a valid identifier\n", args[1]);
	// free_tab(args);
	return ;
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
