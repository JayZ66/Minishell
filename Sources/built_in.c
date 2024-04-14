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

#include "../minishell.h"

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
	}
	else
		exit(0);
}
// Check if else is necessary for errors.

/*
This function will mimic the pwd cmd.
This cmd print the absolute path of
our current working directory.
*/
void	builtin_pwd(void)
{
	char	buffer[1024];
	char	*absolute_path;

	absolute_path = getcwd(buffer, sizeof(buffer));
	if (absolute_path != NULL)
		printf("The absolute path is : %s\n", absolute_path);
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
// Check later if we need to send **char ou *char
// Check how we can get our modify env.
char	**builtin_unset(char **var, char **new_env)
{
	size_t	i;

	i = 0;
	while (new_env[i])
	{
		if (ft_strncmp(new_env[i], var[1], ft_strlen(var[1])) == 0
			&& new_env[i][ft_strlen(var[1])] == '=')
		{
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

// void	builtin_cd(char **env, char **cmd) 
// Check if we need the all cmd ou just path.
// {
// 	size_t	i;
// 	size_t	cwd_len;
// 	char	cwd[1024]; // To change & alloc the right size.
// 	char	*new_pwd;
// 	i = 0;
// 	cwd_len = ft_strlen(cmd[1]);
// 	// new_env = (char **)malloc(sizeof(char) * (ft_size_env(env) + 1));
// 	// if (!new_env)
// 	// {
// 	// 	perror("Can't allocate memory for the env\n");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	new_pwd = (char *)malloc(sizeof(char) * (cwd_len + 5));
// 	if (!new_pwd)
// 	{
// 		perror("Can't allocate memory for the path\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	if (cmd[1] != NULL)
// 	{
// 		if (chdir(cmd[1]) != 0) // Moving from a dir. to another one.
// 		{
// 			perror("Can't moove to the new directory\n");
// 			free(new_pwd);
// 			exit(EXIT_FAILURE);
// 		}
// 		if (getcwd(cwd, cwd_len) == NULL) // Récupérer le new path où on est.
// 		{
// 			perror("Can't get the new path\n");
// 			free(new_pwd);
// 			exit(EXIT_FAILURE);
// 		}
// 		ft_string_cpy(new_pwd, "PWD=");
// 		ft_strcat(new_pwd, cwd, cwd_len);
// 	}
// 	while (env[i])
// 	{
// 		if (ft_strncmp(env[i], "PWD=", 4) == 0)
// 		{
// 			free(env[i]);
// 			env[i] = new_pwd;
// 			// new_env[i] = new_pwd; // Update le path dans l'env.
// 			// printf("%s\n", new_env[i]);
// 			// free(env[i]);
// 		}
// 		printf("env[i] : %s\n", env[i]);
// 		i++;
// 	}
// 	// free(env);
// 	free(new_pwd);
// 	return ;
// }
