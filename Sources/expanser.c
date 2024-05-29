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
ConvertPathToAbsolute
*/

int	is_absolute_path(char **cmd)
{
	size_t	i;
	size_t	is_absolute;

	is_absolute = 0;
	i = 0;
    if (cmd[0])
    {
        while (cmd[0][i])
        {
            if (cmd[0][0] == '/' || cmd[0][0] == '.')
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
Expanser
*/

void	replace_var_of_env(char *content, char *var, int i)
{
	//gerer le cas des quotes ou non avec l'enum 

	// while (content[i] || content[i] != ' ')
	// 	i++;
	if (content[i] == 0)
		content = ft_strdup(var);
	else
		content = ft_strjoin(var, content + i);
	printf("var d'env changee :%s \n", content);

}

// // Enlever le niveau de quote 

char   *remove_first_level_quote(char *content)
{
    int     i;
    int     j;
    int     single_quote;
    int     double_quote;
    char    *temp;

    i = 0;
    j = 0;
    single_quote = 0;
    double_quote = 0;
    temp = (char *)malloc(ft_strlen(content) + 1);
    if (!temp)
    {
        perror("malloc");
        return NULL;
    }
    while (content[i])
    {
        if (content[i] == '\'' && !double_quote)
            single_quote = !single_quote;
        else if (content[i] == '"' && !single_quote)
            double_quote = !double_quote;
        else
            temp[j++] = content[i];
        i++;
    }
    temp[j] = 0;
    return (temp);
}

void    remove_quote(t_final_token *token)
{
    while(token)
    {
        token->content = remove_first_level_quote(token->content);
        token = token->next;
    }
}

int len_of_var_of_env(char *str) {
    int len = 0;
    while (str[len] && (isalnum(str[len]) || str[len] == '_')) {
        len++;
    }
    return len;
}

char *extract_of_the_var(char *str) {
    size_t len = len_of_var_of_env(str + 1);
    char *var = (char *)malloc(len + 2);
    if (var == NULL) {
        return NULL;
    }
    strncpy(var, str, len + 1);
    var[len + 1] = '\0';
    return var;
}

void	get_var_of_env(t_final_token *node) {
    t_final_token *tmp = node;
    char *var;
    size_t i;
    int len;
    char *temp;
    char *final;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (tmp) {
        i = 0;
        while (tmp->content[i]) {
            if (tmp->content[i] == '\'' && !in_double_quote) {
                in_single_quote = !in_single_quote;
            } else if (tmp->content[i] == '\"' && !in_single_quote) {
                in_double_quote = !in_double_quote;
            }

            if (tmp->content[i] == '$' && !in_single_quote) {
                len = len_of_var_of_env(tmp->content + i + 1);
                var = extract_of_the_var(tmp->content + i);
                if (var == NULL) {
                    return;
                }
                
                char *env_value = getenv(var + 1); // skip the '$' character
                if (!env_value) {
                    env_value = ""; // treat undefined variables as empty
                }

                if (i == 0) {
                    final = strdup(env_value);
                    tmp->content = realloc(tmp->content, strlen(final) + 1);
                    strcpy(tmp->content, final);
                } else {
                    temp = strndup(tmp->content, i);
                    final = malloc(strlen(temp) + strlen(env_value) + strlen(tmp->content + i + len + 1) + 1);
                    strcpy(final, temp);
                    strcat(final, env_value);
                    strcat(final, tmp->content + i + len + 1);
                    free(tmp->content);
                    tmp->content = final;
                    free(temp);
                }
                free(var);
            }
            i++;
        }
        tmp = tmp->next;
    }
}
