/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:15:57 by marvin            #+#    #+#             */
/*   Updated: 2024/03/20 14:15:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	main()
- Lire l'entrée utilisateur (chaîne vide ? New line)
- Parsing
- Execution

> Faire tests de chq commande et dès qu'on avance.

Fonction commande : Liste de toutes les commandes
- Déterminer toutes les possibilités de la commande
- Tester toutes les commandes
*/

/*
TOKENISATION : 
- Il faut split notre ligne de commande.
- Fonction pour créer un new node.
- Ajouter dans le contenu du noeud
*/

char	*read_input()
{
	char	*input;

	input = readline(">$");
	add_history(input);
	return (input);
}

int		main(int argc, char **argv, char **env)
{
	char	*input;
	(void)argc;
	(void)argv;
	(void)env;

	while (1)
	{
		input = read_input();
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0) ;
		}
		printf("Vous avez saisi : %s\n", input);
		free(input);
	}
	return (0);
}