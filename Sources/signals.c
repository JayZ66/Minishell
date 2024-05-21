/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 17:31:13 by marvin            #+#    #+#             */
/*   Updated: 2024/04/11 17:31:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_signals(t_minishell *minishell)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
	{
		perror("SIGINT error\n");
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
	sa.sa_handler = sigquit_handler;
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
	{
		perror("SIGINT error\n");
		minishell->last_exit_status = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}

// Fonction qui sera appelée lors de la réception du signal SIGINT (ctrl + c)

void	sigint_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
	}
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

/*
 Vérifie si le signal reçu est effectivement SIGINT.
 Gestion de l'affichage et de la ligne de saisie:
 Vérifie si la ligne de saisie est vide ou si le dernier 
 caractère n'est pas un retour à la lign (rl).
 Si c'est le cas, affiche une nouvelle ligne (\n) pour 
 améliorer la lisibilité de la sortie.
 Remplace la ligne de saisie actuelle par une chaîne vide. (rl)
 Redisplay - Met à jour l'affichage de la ligne de saisie après 
 avoir vidé le contenu.
 Vide le tampon de sortie pour s'assurer que toutes les données 
 sont correctement affichées.
 Force la mise à jour de l'affichage de la ligne de saisie.
  Indique que le prompt a déjà été affiché pour éviter d'en afficher 
  un nouveau lors de la prochaine entrée.
*/

void	sigquit_handler(int sig)
{
	(void)sig;
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
}

// void sigint_handler(int sig) 
// {
// 	(void)sig;
//     printf("\n$ ");  // Affiche un nouveau prompt
//     fflush(stdout);  // Assure que le prompt est bien affiché
// }

// void setup_signal_handlers() 
// {
// 	struct sigaction sa;
//     // Configurer le gestionnaire de signal SIGINT (Ctrl-C)
//     // Configuration du gestionnaire de signal SIGINT et SIGQUIT
//     memset(&sa, 0, sizeof(sa));
//     sa.sa_handler = sigint_handler;
//     sa.sa_flags = 0 ;
//     if (sigaction(SIGINT, &sa, NULL) == -1) {
//         perror("Erreur SIGINT");
//         exit(EXIT_FAILURE);
//     }
// }

// void	sigint_handler(int signo)
// {
// 	if (signo == SIGINT)
// 	{
// 		if (*rl_line_buffer == '\0' || rl_line_buffer[rl_end - 1] != '\n') 
// 			printf("\n");
// 	}
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	fflush(stdout);
// 	rl_forced_update_display();
// 	rl_already_prompted = 1;
// }

// Fonction qui met en place le gestionnaire des signaux.
	/*
	- Déclarer la structure struct sigaction sa. utilisée pour 
	configurer le comportement du gestionnaire de signal.
	struct sigaction sa;
	- initialiser la stucture sa à zero avec memset. pour s'assurer 
	qu'aucun drapeau ou paramètre supp. n'est défini par défaut.
	- Définir la fonction de gestion du signal à appeler lors de la réception
	de SIGINT. Spécifie la fonction sigint_handler comme gestion de signal à 
	appeler lors de la réception de SIGINT
	sa_handler.
	- Aucun drapeau spécifique n'est défini pour le traitement du signal. 
	Aucun drapeau spécial n'est défini pour le traitement du signal.
	sa_flags
	- Enregistrer le gestionnaire de signal pour SIGINT avec
	la configuration sa. Enregistre le gestionnaire de signal spécifié 
	(sigint_handler) pour le signal SIGINT en utilisant sigaction().
	sigaction et vérification retour -1 ou autre.
	*/