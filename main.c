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

/*
1. Lexer
2. Historique, signal, buildins, etc.
*/


char	*read_input()
{
	char	*input;

	input = readline(">$");
	if (input == NULL)
	{
		perror("Input is null\n");
		EXIT_FAILURE;
	}
	if (ft_strlen(input) <= 0)
	{
		perror("Input is empty\n");
		exit(0);
	}
	add_history(input);
	return (input);
}

int		main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*token;
	(void)argc;
	(void)argv;
	(void)env;

	token = NULL;
	if (argc != 1 || argv[1])
		return (perror("Wrong nb of args\n"), 1);
	while (1)
	{
		input = read_input();
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0) ;
		}
		// printf("Vous avez saisi : %s\n", input);
		token = extract_cmd(&token, input);
		if (!token)
			return(perror("Extract cmd failed\n"), free(input), 1);
		free(input);
	}
	return (0);
}


//  cmd -l < file1 | cmd|cmd -a > file2
//  1. Boucle tant que je vois pas de pipe (puis boucle ext. tant que pas fini puis pipe)
//  2. Si redirection : cmd -l (en token cmd) < file1 (token input) => Garder cmd -l dans une string. 
//  que l'on met dans un noeud
//  3. Token : Faire tous les cas (arbre) puis token avec conditions

// Envoyer dans mon pipex (simuler sur argc/argv, et envoyer env. de mon minishell avec getenv).

//  Pipe aussi dans un node.

//  Lexer : 
//  Extrait les redirections puis envoie à pipex
//  1. Check erreur avec tokenisation puis 2ème prog. pour transformer la string et l'envoyer à pipex.
//  $? (donne erreur 0/1) => Récupèrer le result de la cmd d'avant. 
//  => Donc à voir comment faire. + voir si pls cmd. 
//  => Execve renvoie 1/0 donc voir comment le récupérer.
 
// FIRST TO DO.
// Check la correction pour voir si rien de bad pour use pipex.
// LIGNE A SUIVRE : 
// Mettre dans une liste chaînée ma str de départ. > Faire les tokens.
// Gérer les erreurs avec les tokens. > Transformer ma liste chaînée en
// string qui sera modifée pour convenir à pipex (cf. ci-dessous) et la modifier
// pour convenir à l'entrée attendue par pipex.
// Identifier mes redirections (tokeniser avec input/output) pour derrière pouvoir
// bien former ma string pour pipex (au niveau des redirections).

// Tenter pipex (interne à minishell) 
// Faire getenv() => Tab. de tab. je cherche shell level de 1 à 2. (SHLVL) like path (pipex)
// Dans mon minishell j'ai un tab. de tab. de env. => J'envoie ça dans mon pipex
// => Modifier la fonction get_env dans pipex.

// STEPS TO FOLLOW :
// Tokenisation au début et on met dans les nodes (cf ci-dessus)
// On transforme cela en une string qui convient à pipex (fonction et plus prog.)
// On transforme argc (on le calcule avec la new string), on transforme argv (string) et env.
// avec l'environnement que l'on a modifié dans minishell (comme la fonction get_path mais où avant on
// check SHLVL qu'on modifie de 1 à 2 et qu'on envoie ensuite).
// On gère le $? Check comment l'extraire.
// Gérer les erreurs (en checkant et testant tout à la main).

// Questions à vérifier : 
// Imaginons qu'il y ait 3 inputs et 1 output comment le gérer avec pipex ?
// Bien passer l'env. à qu'on crée dans un main à pipex. 
// Est-ce qu'on peut bien récupérer de pipex le $?