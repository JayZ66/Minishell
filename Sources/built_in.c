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


char	**is_char_ok(char **args)
{
	size_t	i;
	size_t	j;
	size_t	count_char;

	i = 0;
	count_char = 0;
	while (args[1][i])
	{
		if (args[1][i] == '-' || args[1][i] == '+')
			count_char++;
		else if (ft_isdigit(args[1][i]) == 0 && (args[1][i] != '-' && args[1][i] != '+'))
		{
			printf("bash: exit: %s: numeric argument required\n", args[1]);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	if (count_char > 1)
	{
		printf("bash: exit: %s: numeric argument required\n", args[1]);
		exit(EXIT_FAILURE);
	}
	else
	{
		i = 0;
		j = 0;
		while (args[1][i])
		{
			if (args[1][i] != '-' || args[1][i] != '+')
			{
				args[1][j] = args[1][i];
				j++;
			}
			i++;
		}
	}
	return (args);
}

/*
This function will mimic the exargs = is_char_ok(args);
		if (args == NULL)
			return ;it cmd.
It'll exit the prog. based on the given output code.
*/

/*
To handle : 
- exit 666 666 => Trop d'args. => DONE
- exit 666 666 666 666 => DONE
- exit 666 hola 666 => DONE
- exit -NOMBRES => Doit fonctionner => DONE
- exit +NOMBRES => Doit fonctionner => DONE
- Si un niveau de quotes doit marcher !
- Si pls caractères spéciaux : 
quotes / + / - / etc.  => DONE
=> erreur need numeric arg.
- exit 9223372036854775807
Erreur a gerer => minishell: malloc.c:2617: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
Aborted (core dumped)
*/
void	builtin_exit(char **args, t_minishell *exit_code)
{
	size_t	i;
	int		exit_status;

	i = 0;
	exit_status = 0;
	if (args[1] != NULL)
	{
		args = is_char_ok(args);
		if (args == NULL)
			return ;
		if (args[2] != NULL)
		{
			printf("-bash: exit: too many arguments\n");
			return ;
		}
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
		exit_code->last_exit_status = exit_status;
		printf("exit_status : %i\n", exit_status);
		if (exit_status >= 0 && exit_status <= 255)
			exit(exit_status);
	}
	else
	{
		exit_code->last_exit_status = 0;
		exit(0);
	}
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


void	builtin_unset(char **var, t_minishell *minishell)
{
	size_t	i;
	size_t	j;
	// int		is_unset;
	// char	**new_env = minishell->env; // Check pour leaks !

	j = 1;
	// is_unset = 0;
	if (var[1])
	{
		while (var[j])
		{
			i = 0;
			if (identifier_errors_unset(var[j]) == 1)
			{
				if (var[j + 1] == NULL)
					break ;
			}
			while (minishell->env[i])
			{
				if (ft_strncmp(minishell->env[i], var[j], ft_strlen(var[j])) == 0
					&& minishell->env[i][ft_strlen(var[j])] == '=')
				{
					while (minishell->env[i + 1])
					{
						minishell->env[i] = minishell->env[i + 1];
						i++;
					}
					minishell->env[i] = NULL;
					// is_unset = 1;
				}
				i++;
			}
			j++;
		}
	}
	// if (is_unset == 0)
	// 	perror("Can't find the var. to remove from the env.\n");
	return ;
}

/*
This function mimic the unset cmd.
It allows us to delete one or more
environment var.
*/
// Check later if we need to send **char ou *char
// Check how we can get our modify env.
// void	builtin_unset(char **var, t_minishell *minishell)
// {
// 	size_t	i;
// 	// char	**new_env = minishell->env; // Check pour leaks !

// 	i = 0;
// 	if (var[1])
// 	{
// 		while (minishell->env[i])
// 		{
// 			if (ft_strncmp(minishell->env[i], var[1], ft_strlen(var[1])) == 0
// 				&& minishell->env[i][ft_strlen(var[1])] == '=')
// 			{
// 				while (minishell->env[i + 1])
// 				{
// 					minishell->env[i] = minishell->env[i + 1];
// 					i++;
// 				}
// 				minishell->env[i] = NULL;
// 				return ;
// 			}
// 			i++;
// 		}
// 		perror("Can't find the var. to remove from the env.\n");
// 		return ;
// 	}
// 	return ;
// }

void	builtin_env(t_minishell *minishell)
{
	size_t	i;

	i = 0;
	while (minishell->env[i])
	{
		printf("%s\n", minishell->env[i]);
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
