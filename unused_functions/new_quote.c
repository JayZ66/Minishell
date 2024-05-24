/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 17:26:03 by marvin            #+#    #+#             */
/*   Updated: 2024/05/12 17:26:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* gestion_guillemets(char* commande) {
    int longueur = strlen(commande);
    char* nouvelle_commande = (char*)malloc((longueur + 1) * sizeof(char));
    if (nouvelle_commande == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }

    int index_nouvelle_commande = 0;
    int guillemet = 0; // Indique le type de guillemet ouvert (0 pour pas de guillemets, 1 pour guillemets simples, 2 pour guillemets doubles)

    for (int i = 0; i < longueur; i++) {
        // Si on rencontre un guillemet simple ou double
        if (commande[i] == '\'' || commande[i] == '"') {
            if (guillemet == 0) {
                guillemet = (commande[i] == '\'') ? 1 : 2;
            } else if ((guillemet == 1 && commande[i] == '\'') || (guillemet == 2 && commande[i] == '"')) {
                guillemet = 0;
            }
            // Ne pas copier le guillemet ouvert si les guillemets sont fermés
            if (guillemet != 0) {
                continue;
            }
        }
        // Ne copier que les caractères qui ne sont pas entre guillemets simples
        if (guillemet != 1 || (guillemet == 1 && commande[i] != '\'')) {
            nouvelle_commande[index_nouvelle_commande++] = commande[i];
        }
    }

    nouvelle_commande[index_nouvelle_commande] = '\0';

    return nouvelle_commande;
}

int main() {
    char* ligne_de_commande1 = "echo 'Bonjour, monde!' cat output.txt";
    char* ligne_de_commande2 = "echo 'bonjour \"monde!\"'";

    char* nouvelle_ligne_de_commande1 = gestion_guillemets(ligne_de_commande1);
    printf("Ligne de commande sans guillemets 1: %s\n", nouvelle_ligne_de_commande1);

    char* nouvelle_ligne_de_commande2 = gestion_guillemets(ligne_de_commande2);
    printf("Ligne de commande sans guillemets 2: %s\n", nouvelle_ligne_de_commande2);

    free(nouvelle_ligne_de_commande1);
    free(nouvelle_ligne_de_commande2);

    return 0;
}







