/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:20:20 by marvin            #+#    #+#             */
/*   Updated: 2024/03/21 15:20:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Localiser les sep. (pipe & redirections) < > >> << |
Tout ce qui est entre on met dans le noeud (entiereté de la cmd)
On split ensuite
*/

t_token	*extract_cmd(t_token **token, char *cmd_line)
{
	size_t	i;
	size_t	start;
	char	*cmd;
	t_token	*new;

	i = 0;
	new = NULL;
	while (cmd_line[i] && cmd_line[i] != '\n')
	{
		while (cmd_line[i] && cmd_line[i] == 32)
			i++;
		start = i;
		while ((cmd_line[i] && cmd_line[i] != '|'))
			i++;
		if (i > start)
		{
			cmd = ft_strndup(cmd_line + start, i - start);
			printf("Taille envoyée : %ld\n", i - start);
			printf("cmd après strndup : %s\n", cmd);
			if (!cmd)
				return(perror("Can't get cmd\n"), NULL);
			new = init_node(cmd);
			if (!new)
				return(perror("Can't init my node\n"), free(cmd), NULL);
			add_back(token, new);
			printf("Contenu de mon noeud : %s\n", new->content);
			free(cmd);
		}
		i++;
	}
	return (*token);
}


// Je crée une str, avec strdup, où je récupère jusqu'au pipe.
// Une fois que j'ai récupéré mon bout de str. je l'envoie pour créer un new node.
// Ensuite je l'envoie dans add_back pour l'ajouter au bout de ma liste chaînée.
