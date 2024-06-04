/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romlambe <romlambe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 10:01:14 by jeguerin          #+#    #+#             */
/*   Updated: 2024/06/04 14:29:59 by romlambe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
		{
			return ((char *)s + i);
		}
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

int	ft_strnchr(const char *str, int c)
{
	char	*ptr;
	int		i;

	ptr = (char *)str;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}

// int	ft_strschr(const char *str, char *ligne)
// {
// 	int		i;
// 	size_t	j;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == ligne[j] && str[i + 1] == ligne[j + 1])
// 			return (0);
// 		else if (str[i] == ligne[j] && str[i + 1] == ligne[j + 1]
// 			&& str[i + 2] == ligne[j + 2])
// 			return (0);
// 		i++;
// 	}
// 	return (i);
// }

int ft_strschr(const char *str, char *ligne)
{
    int i;
    // int j;	
    int len_str;
    int len_ligne;

    i = 0;
    // j = 0;
    len_str = strlen(str);
    len_ligne = strlen(ligne);

    while (i < len_str)
    {
        // Check if the remaining part of 'str' is long enough for 'ligne'
        if (i + len_ligne <= len_str)
        {
            if (strncmp(&str[i], ligne, len_ligne) == 0)
                return (0);
        }
        i++;
    }
    return (i);
}