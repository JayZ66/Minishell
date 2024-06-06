/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeguerin <jeguerin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 09:42:20 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/06 17:01:15 by jeguerin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	*ft_strncpy(char *dest, const char *src, size_t n)
// {
// 	size_t	i;

// 	i = 0;
// 	if (n == 0)
// 		return (NULL);
// 	while (src[i] && i < n)
// 	{
// 		dest[i] = src[i];
// 		i++;
// 	}
// 	dest[i] = '\0';
// 	return (dest);
// }

// static size_t	ft_countwords(char *str, char c)
// {
// 	int		i;
// 	size_t	countw;

// 	i = 0;
// 	countw = 0;
// 	while (str[i])
// 	{
// 		while (str[i] && str[i] == c)
// 			i++;
// 		if (str[i] && str[i] != c)
// 			countw++;
// 		while (str[i] && str[i] != c)
// 			i++;
// 	}
// 	return (countw);
// }

// static char	**malloc_tab(const char *s, char c)
// {
// 	char	**new;

// 	new = (char **)malloc(sizeof(char *) * (ft_countwords((char *)s, c) + 1));
// 	if (new == NULL)
// 		return (NULL);
// 	return (new);
// }

// static void	extra(char const *s, int *i, int *j, char c)
// {
// 	while (s[*i] && s[*i] == c)
// 		(*i)++;
// 	*j = *i;
// }

// char	**ft_split(char const *s, char c)
// {
// 	int		i;
// 	int		j;
// 	int		word;
// 	char	**new;

// 	i = 0;
// 	word = -1;
// 	new = malloc_tab(s, c);
// 	if (!new)
// 		return (NULL);
// 	while (s[i])
// 	{
// 		extra(s, &i, &j, c);
// 		while (s[i] && s[i] != c)
// 			i++;
// 		if (i > j)
// 		{
// 			new[++word] = (char *)malloc(sizeof(char) * ((i - j) + 1));
// 			if (!new[word])
// 				return (NULL);
// 			ft_strncpy(new[word], &s[j], i - j);
// 		}
// 	}
// 	new[word + 1] = NULL;
// 	return (new);
// }

static int	ft_allocate(char **tab, char const *s, char sep, size_t *h_error)
{
	char		**tab_p;
	char const	*tmp;

	tmp = s;
	tab_p = tab;
	while (*tmp)
	{
		while (*s == sep)
			s++;
		tmp = s;
		while (*tmp && *tmp != sep)
			tmp++;
		if (*tmp == sep || tmp > s)
		{
			*tab_p = ft_substr(s, 0, tmp - s);
			if (!*tab_p)
				return (0);
			s = tmp;
			tab_p++;
			(*h_error)++;
		}
	}
	*tab_p = NULL;
	return (1);
}

static int	ft_count_words(char const *s, char sep)
{
	int	word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == sep)
			s++;
		if (*s)
			word_count++;
		while (*s && *s != sep)
			s++;
	}
	return (word_count);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		size;
	size_t	h_error;

	if (!s)
		return (NULL);
	h_error = 0;
	size = ft_count_words(s, c);
	new = (char **)ft_malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (NULL);
	new[size] = 0;
	if (!ft_allocate(new, s, c, &h_error))
	{
		while (h_error > 0)
		{
			free(new[h_error - 1]);
			h_error--;
		}
		free(new);
		return (NULL);
	}
	return (new);
}
