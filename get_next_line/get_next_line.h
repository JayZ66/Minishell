/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:22:31 by jeguerin          #+#    #+#             */
/*   Updated: 2024/04/10 18:36:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

char	*get_next_line(int fd);
int		ft_strlen_gnl(char *str);
int		ft_strchr_gnl(const char *str, int c);
char	*ft_strndup_gnl(const char *str, int size);
char	*ft_join(char *s1, char *s2);
char	*update_stash(char *stash);
char	*extract_line(char *stash);

#endif
