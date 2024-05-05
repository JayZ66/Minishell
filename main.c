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


char	*read_input()
{
	char	*input;

	input = readline(">$");

	add_history(input);
	return (input);
}

void	print_new_env(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{
		printf("Voici mon new env. : %s\n", env[i]);
		i++;
	}
}


int		main(int argc, char **argv, char **env)
{
	char	*input;
	t_token	*token;
	t_clean_token *clean_token;
	// t_token *clean_token;
	// char	*cmd_line;
	(void)argc;
	(void)argv;

	token = NULL;
	clean_token = (t_clean_token *)malloc(sizeof(t_clean_token));
	// clean_token = NULL;
	// if (argc != 1 || argv[1])
	// 	return (perror("Wrong nb of args\n"), 1);
	while (1)
	{
		input = read_input();
		if (ft_strcmp(input, "exit") == 0)
		{
			free(input);
			exit(0) ;
		}

		token = extract_cmd(&token, input, env);
		if (!token)
		{
			return 0;
		}
		t_token *head = token;
		clean_chevron(token);
		clean_spaces(token);

		printf("%s|\n", token->content);
		manage_node(token);
		clean_spaces2(token);
		// print_lst(token);
		token = head;
		printf("token = %s\n", token->content);
		clean_token = copy_lst(token);
		print_clean_lst(clean_token);
		test_redirection_input(clean_token);

		free_that_lst(&token);
		free_that_clean_lst(&clean_token);


		//gerer les builtins car si je mets un espace pb
		//pb sur pwd pour le moment

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
// Récupèrer env., modifier le shell level & envoyer à pipex.
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