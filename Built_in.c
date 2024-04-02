/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 13:20:52 by marvin            #+#    #+#             */
/*   Updated: 2024/04/01 13:20:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

/*
This function will mimic the exit cmd.
It'll exit the prog. based on the given output code.
*/
void	builtin_exit(char **args)
{
	size_t	i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	if (args[1] != NULL)
	{
		while (args[1][i])
		{
			if (ft_isdigit(args[1][i]) == 0)
			{
				perror("The output code must be a numeric arg.\n");
				exit(EXIT_FAILURE);
			}
			i++;
		}
		exit_status = ft_atoi(args[1]);
		if (exit_status >= 0 && exit_status <= 255)
		{
			printf("Exit_status : %d\n", exit_status);
			exit(exit_status);
		}
	} // Check if else is necessary for errors.
	else
		exit(0);
}


/*
This function will mimic the pwd cmd.
This cmd print the absolute path of
our current working directory.
*/
void	builtin_pwd()
{
	char	buffer[1024];
	char	*absolute_path;

	absolute_path = getcwd(buffer, sizeof(buffer));
	if (absolute_path != NULL)
		printf("The absolute path of the current directory is : %s\n", absolute_path);
	else
	{
		perror("Can't get the absolute path\n");
		exit(EXIT_FAILURE);
	}
}

/*
This function mimic the unset cmd.
It allows us to delete one or more
environment var.
*/
char	**builtin_unset(char *var, char **new_env) // TO TEST.
{ // Check what kind of var. we need ($ ou pas). + how we can get our modify env.
	char	*path;
	size_t	i;

	i = 0;
	while (new_env[i])
	{
		path = new_env[i];
		if (ft_strncmp(path, var, ft_strlen(var)) == 0 && path[ft_strlen(var)] == '=')
		{
			free(new_env[i]);
			while (new_env[i + 1])
			{
				new_env[i] = new_env[i + 1];
				i++;
			}
			new_env[i] = NULL;
			return (new_env);
		}
		i++;
	}
	perror("Can't find the var. to remove from the env.\n");
	return (NULL);
}

void	builtin_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/*
cd : Il faut use change directory & ensuite update le
path dans l'env.
*/