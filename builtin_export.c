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

#include "minishell.h"

/*
Check if the var. is in the
existing environment.
*/

int	is_var_in_env(char *var, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			return (1);
		i++;
	}
	return (0);
}

/*
Will modify the value of the identified
var. in the environment.
*/

char	**modify_value_env(char **env, char *var, char *new_value)
{
	size_t	i;
	size_t	var_len;
	size_t	size_env;
	char	**new_env;

	i = 0;
	// new_env = NULL;
	var_len = ft_strlen(var);
	size_env = ft_size_env(env);
	new_env = (char **)malloc(sizeof(char *) * (size_env + 1));
	if (!new_env)
	{
		perror("Can't create the new env.\n");
		exit(EXIT_FAILURE);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], var, var_len) == 0 && env[i][var_len] == '=')
			env[i] = ft_string_cpy(env[i] + var_len, new_value);
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	// i = 0;
	// while (env[i])
	// {
	// 	new_env[i] = ft_strdup(env[i]);
	// 	// free(env[i]);
	// 	i++;
	// }
	free(env);
	new_env[size_env] = NULL;
	return (new_env);
}

size_t	ft_size_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**create_var_env(char **env, char *var)
{
	size_t	size_env;
	size_t	i;
	char	**new_env;

	size_env = ft_size_env(env);
	// printf("var. to add : %s\n", var);
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

void	sort_tab(char **env)
{
	size_t	i;
	// size_t	j;
	char	*temp;

	i = 0;
	// j = 0;
	while (env[i + 1])
	{
		if (env[i][0] > env[i + 1][0] || 
               (env[i][0] == env[i + 1][0] && env[i][1] > env[i + 1][1]))
		{
			temp = env[i];
			env[i] = env[i + 1];
			env[i + 1] = temp;
			i = 0;
		}
		else
			i++;
	}
	// return (env);
}

char	**builtin_export(char **args, char **env)
{
	size_t	i;
	// size_t	j;
	char	*var;
	char	**new_env;

	i = 0;
	if (args[1] != NULL)
	{
		while(args[1][i]) // On check la forme de l'arg.
		{
			if (args[1][i] == '=')
			{
				var = ft_substr(args[1], 0, i);
				if (is_var_in_env(var, env) == 1)
				{
					new_env = modify_value_env(env, var, args[1] + i);
					free(var);
					return (new_env); // CHECK HOW TO MANAGE LEAKS WITH ENV.
					// Modification de la valeur de la var.
				}
				else
				{
					new_env = create_var_env(env, args[1]);
					free(var);
					return (new_env);
					// Création var. dans l'env.
				}

			}
			i++;
		}
	}
	else
	{
		sort_tab(env);
		while(env[i])
		{
			printf("declare -x %s\n", env[i]); // METTRE ORDRE ALPHA.
			i++;
		}
		return (env);
		// On affiche l'env.
	}
	perror("The cmd is not the export we're expected\n");
	return (NULL);
}

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