/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 10:56:42 by marvin            #+#    #+#             */
/*   Updated: 2024/03/01 10:56:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "Libft/libft.h"
// # include "get_next_line/get_next_line.h"
// # include "printf/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

// Une structure token
// token cmd;
// token arg;
// token options;

typedef enum 
{
    CMD,
    OPTION,
    ARG,
    OPERATOR
} Token_type;

typedef struct	s_token
{
	char			**content;
	Token_type		type;
	struct s_token	*next;
} t_token;

typedef struct s_exec
{
	char	**path;
	char	*cmd;
} t_exec;


typedef struct s_minishell
{
	t_token	*token;
	t_exec	exec;
} t_minishell;


// Une structure outils
// path
// envp
// cmd
// args
// here_doc
// pipes
// pid


// MANDATORY PART
char	*read_input();


#endif