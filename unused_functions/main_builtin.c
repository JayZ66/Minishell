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

#include "../minishell.h"

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


// int	main(int argc, char **argv, char **env)
// {
// 	char	*input;
// 	char	**new_env;
// 	// t_token	*token;

// 	manage_signals();
// 	(void)argc;
// 	(void)argv;
// 	// token = NULL;
// 	// if (argc != 1 || argv[1])
// 	// 	return (perror("Wrong nb of args\n"), 1);
// 	new_env = realloc_env(env);
// 	if (env == NULL)
// 		return (perror("Realloc env. failed\n"), 1);
// 	while (1)
// 	{
// 		input = read_input();
// 		if (ft_strcmp(input, "exit") == 0)
// 		{
// 			free(input);
// 			exit(0);
// 		}
// 		else if (ft_strcmp(input, "cd") == 0)
// 		{
// 			break ;
// 		}
// 		// token = extract_cmd(&token, input, env);
// 		// if (!token)
// 		// 	return(perror("Extract cmd failed\n"), free(input), 1);
// 	}
// 	print_new_env(env);
// 	// char *args[] = {"cd", "/home/jeza/Projects/Minishell1", NULL};
// 	// char *args[] = {"cd", "/", NULL};
// 	// char *args[] = {"cd", "..", NULL};
// 	// char *args[] = {"cd", "Libft/", NULL};
// 	char *args[] = {"cd", NULL};
// 	new_env = builtin_cd(new_env, args);
// 	// char *args[] = {"export", "LS_COLORS=Trop de truc à écrire", NULL};
// 	// char *args[] = {"export", "LOL=osef", NULL};
// 	// char *args[] = {"export", NULL};
// 	// new_env = builtin_export(args, new_env);
// 	print_new_env(new_env);
// 	free(input);
// 	// free_that_lst(&token);
// 	// if (env != NULL)
// 	free_tab(new_env);
// 	// free_tab(env);
// 	return (0);
// }

//  cmd -l < file1 | cmd|cmd -a > file2
//  1. Boucle tant que je vois pas de pipe (puis boucle ext. tant 
// que pas fini puis pipe)
//  2. Si redirection : cmd -l (en token cmd) < file1 (token input) 
// => Garder cmd -l dans une string.
//  que l'on met dans un noeud
//  3. Token : Faire tous les cas (arbre) puis token avec conditions

//  Lexer :
//  Extrait les redirections puis envoie à pipex
//  1. Check erreur avec tokenisation puis 2ème prog. pour transformer 
// la string et l'envoyer à pipex.
//  $? (donne erreur 0/1) => Récupèrer le result de la cmd d'avant. 
// ==> FAIRE VAR. STRUCTURE !
//  => Donc à voir comment faire. + voir si pls cmd.
//  => Execve renvoie 1/0 donc voir comment le récupérer. 
// ==> AU MOMENT DE L'EXEC. ON RECUP RESULT.

// Identifier mes redirections (tokeniser avec input/output) pour 
// derrière pouvoir bien former ma string pour pipex 
// (au niveau des redirections).

// Tenter pipex (interne à minishell)
// Faire getenv() => Tab. de tab. je cherche shell level de 1 à 2. 
// (SHLVL) like path (pipex)
// Dans mon minishell j'ai un tab. de tab. de env. 
// => J'envoie ça dans mon pipex
// => Modifier la fonction get_env dans pipex.

// STEPS TO FOLLOW :
// Tokenisation au début et on met dans les nodes (cf ci-dessus)
// On transforme cela en une string qui convient à pipex 
// (fonction et plus prog.)
// On transforme argc (on le calcule avec la new string), 
// on transforme argv (string) et env.
// avec l'environnement que l'on a modifié dans minishell 
// (comme la fonction get_path mais où avant on
// check SHLVL qu'on modifie de 1 à 2 et qu'on envoie ensuite).
// On gère le $? Check comment l'extraire.
// Gérer les erreurs (en checkant et testant tout à la main).


// Main test fonctions built_in et env !!

// int		main(int argc, char **argv, char **env)
// {
// 	char	*input;
// 	t_token	*token;
// 	// char	*cmd_line;
// 	// char	*var;
// 	char	**new_env;
// 	(void)argc;
// 	(void)argv;

// 	token = NULL;
// 	// if (argc != 1 || argv[1])
// 	// 	return (perror("Wrong nb of args\n"), 1);
// 	while (1)
// 	{
// 		input = read_input();
// 		if (ft_strcmp(input, "exit") == 0)
// 		{
// 			free(input);
// 			exit(0) ;
// 		}
// 		else if (ft_strcmp(input, "unset") == 0)
// 		{
// 			char	*args[] = {"unset", "USER", NULL};
// 			new_env = builtin_unset(args, env);
// 			print_new_env(new_env);
// 		}
// 		// else if (ft_strcmp(input, "export") == 0)
// 		// {
// 		// 	// char *args[] = {"export", 
//		"LS_COLORS=Trop de truc à écrire", NULL};
// 		// 	char *args[] = {"export", "LOL=osef", NULL};
// 		// 	// char *args[] = {"export", NULL};
// 		// 	new_env = builtin_export(args, env);
// 		// 	print_new_env(new_env);
// 		// }
// 		// else if (ft_strcmp(input, "debug_exit") == 0) 
// 		// {
// 		// 	char *args[] = {"debug_exit", "142", NULL};
// 		// 	builtin_exit(args);
// 		// 	free(input);
//     	// }
// 		// shell_level(env); 
// => To put at the right place for not having diff. SHLVL
// 		// if (ft_strcmp(input, "pwd") == 0)
// 		// 	builtin_pwd();
// 		token = extract_cmd(&token, input, env);
// 		if (!token)
// 			return(perror("Extract cmd failed\n"), free(input), 1);
// 		//  var = get_the_var_of_env(token);
// 		// print_lst(token);		

// 		// cmd_line = check_line_cmd(token);
// 		// char	**final_str;
// 		// final_str = ft_split(cmd_line, ' ');
// 		// execute_pipe(ft_strlen(cmd_line), final_str, env); // Wrong because
// 		free(input);
// 		// free_tab(new_env);
// 		free_that_lst(&token);
// 	}
// 	return (0);
// }
