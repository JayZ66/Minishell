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
char	**builtin_unset(char **var, char **new_env) // Check later if we need to send **char ou *char
{ // Check how we can get our modify env.
	size_t	i;

	i = 0;
	while (new_env[i])
	{
		if (ft_strncmp(new_env[i], var[1], ft_strlen(var[1])) == 0 && new_env[i][ft_strlen(var[1])] == '=')
		{
			// free(new_env[i]); // Can't free bce i've an invalid pointer. So, maybe send it to the new_env ?
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

void	builtin_cd(char **env, char **cmd)
{
	size_t	i;

	i = 0;
	if (cmd[1] != NULL)
	{
		if (chdir(cmd[1]) != 0)
		{
			perror("Can't moove to the new directory\n");
			return ;
		}
		char cwd[1024]; // To change & alloc the right size.
		if (getcwd(cwd, sizeof(cwd)) == NULL) // Récupérer le new path où on est.
		{
			perror("getcwd");
			return;
		}

		char *new_pwd = malloc(strlen("PWD=") + strlen(cwd) + 1);
		if (new_pwd == NULL) {
			perror("malloc");
			return;
		}

		sprintf(new_pwd, "PWD=%s", cwd);
	}
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
		{
			free(env[i]);
			env[i] = new_pwd;
			break ;
		}
		i++;
	}
}