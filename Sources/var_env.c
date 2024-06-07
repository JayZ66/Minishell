/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 16:03:05 by romlambe          #+#    #+#             */
/*   Updated: 2024/06/07 11:05:41 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_var_of_env(t_final_token *node, t_minishell *minishell)
{
	t_final_token	*tmp;
	int				in_single_quote;
	int				in_double_quote;
	char			*nb;

	tmp = node;
	in_single_quote = 0;
	in_double_quote = 0;
	while (tmp)
	{
		if (get_exit_code(tmp->content, minishell) == 1)
		{
			nb = ft_itoa(minishell->last_exit_status);
			tmp->content = nb;
		}
		else
			process_token_content(tmp, minishell, &in_single_quote,
				&in_double_quote);
		tmp = tmp->next;
	}
}

int	handle_env_var(t_final_token *tmp, t_minishell *minishell, size_t *i)
{
	char	*var;
	char	*env_value;
	int		len;

	len = len_of_var_of_env(tmp->content + *i + 1);
	var = extract_of_the_var(tmp->content + *i);
	if (var == NULL)
	{
		if (*var == '$')
			ft_free(var);
		return (0);
	}
	env_value = select_var_of_env(minishell, var + 1);
	ft_free(var);
	if (!env_value)
		return (tmp->content = "", 0);
	if (*i == 0)
	{
		if (!replace_content_start(tmp, env_value))
			return (ft_free(env_value), 0);
	}
	else
		if (!replace_content_middle(tmp, env_value, *i, len))
			return (ft_free(env_value), 0);
	return (ft_free(env_value), 1);
}

int	replace_content_start(t_final_token *tmp, char *env_value)
{
	tmp->content = ft_realloc(tmp->content, ft_strlen(env_value) + 1);
	if (!tmp->content)
		return (0);
	ft_string_cpy(tmp->content, env_value);
	return (1);
}

int	replace_content_middle(t_final_token *tmp,
	char *env_value, size_t i, int len)
{
	char	*temp;
	char	*final;

	temp = ft_strndup(tmp->content, i);
	if (!temp)
		return (0);
	final = ft_malloc(strlen(temp) + ft_strlen(env_value)
			+ ft_strlen(tmp->content + i + len + 1) + 1);
	if (!final)
		return (0);
	ft_string_cpy(final, temp);
	ft_strcat(final, env_value, ft_strlen(env_value));
	ft_strcat(final, tmp->content + i + len + 1,
		ft_strlen(tmp->content + i + len + 1));
	ft_free(tmp->content);
	tmp->content = final;
	return (1);
}

void	process_token_content(t_final_token *tmp, t_minishell *minishell,
	int *in_single_quote, int *in_double_quote)
{
	size_t	i;

	i = 0;
	while (tmp->content[i])
	{
		update_quotes(tmp->content[i], in_single_quote, in_double_quote);
		if (tmp->content[i] == '$' && !(*in_single_quote))
		{
			if (!handle_env_var(tmp, minishell, &i))
				return ;
		}
		i++;
	}
}

// void	get_var_of_env(t_final_token *node, t_minishell *minishell) {
//     t_final_token *tmp;
//     char *var;
//     size_t i;
//     int len;
//     char *temp;
//     char *final;

// 	(void)minishell;
// 	tmp = node;
//     int in_single_quote = 0;
//     int in_double_quote = 0;
//     while (tmp) {
//         i = 0;
//         if (!tmp->content)
//         {
//             ft_free(tmp);
//             break ;
//         }
//         while (tmp->content[i]) {
//             if (tmp->content[i] == '\'' && !in_double_quote) {
//                 in_single_quote = !in_single_quote;
//             } else if (tmp->content[i] == '\"' && !in_single_quote) {
//                 in_double_quote = !in_double_quote;
//             }
//             if (tmp->content[i] == '$' && !in_single_quote) {
//                 len = len_of_var_of_env(tmp->content + i + 1);
//                 var = extract_of_the_var(tmp->content + i);
//                 if (var == NULL) {
//                     return;
//                 }
//                 char *env_value = select_var_of_env(minishell, var + 1);
//                 if (!env_value) {
//                     env_value = ""; // treat undefined variables as empty
//                 }

//                 if (i == 0) {
//                     final = ft_strdup(env_value);
//                     tmp->content = ft_realloc(tmp->content,
//						strlen(final) + 1);
//                     strcpy(tmp->content, final);
//                 } else {
//                     temp = ft_strndup(tmp->content, i);
//                     final = ft_malloc(ft_strlen(temp) + ft_strlen(env_value)
//							+ ft_strlen(tmp->content + i + len + 1) + 1);
//                     ft_string_cpy(final, temp);
//                     ft_strcat(final, env_value, ft_strlen(env_value));
//                     ft_strcat(final, tmp->content + i + len + 1,
//							ft_strlen(tmp->content + i + len + 1));
//                     ft_free(tmp->content);
//                     tmp->content = final;
//                     // ft_free(temp);
//                 }
//                 ft_free(var);
//             }
//             i++;
//         }
//         tmp = tmp->next;
//     }
// }
