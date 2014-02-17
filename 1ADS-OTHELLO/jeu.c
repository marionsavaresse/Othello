#include <stdio.h>
#include <stdlib.h>

#include "plateau.h"
#include "pose.h"
#include "possibilites.h"
#include "sauvegarde.h"
#include "modesOrdinateur.h"
#include "jeu.h"



void jeuDeux(s_partie *partie)
{
    char choixPartieTemp[2] = {}; char choixPartie = 0; int sauvegarde = 0; int caseLigne = 0; int caseColonne = 0;
    
    printf("\n");
    initialise(partie);
    printf("Pour sauvegarder en cours de partie :\n-> Entrer ligne = 0 et colonne = x \n\n");
    
    // CHOIX DE COMMENCER OU CONTINUER UNE PARTIE
    do
    {
        printf("Voulez-vous commencer une nouvelle partie <1> ou en continuer une <2> ? ");
        // %1s RECUPERE LE CARACTERE ET LE RETOUR CHARIOT
        scanf("%1s",choixPartieTemp);
        // LE CARACTERE ETANT LE 0 ON LE RECUPERE AINSI
        choixPartie = choixPartieTemp[0];
        // PERMET D'EVITER UN BUG D'AFFICHAGE EN VIDANT LES CARACTERES TAPES QUI SONT EN MEMOIRE (VIDE MEMOIRE STDIN)
        while(getchar() != '\n')
        {
            continue;
        }

    } while ((choixPartie != '1') && (choixPartie != '2'));
    
    // CHARGEMENT DU FICHIER DE SAUVEGARDE
    if (choixPartie == '2')
    {
        initialiseFichier(partie);
    }
    
    printf("\n\n");
    affiche(*partie);

    // CONDITION D'ARRET DU JEU QUAND AUCUN JOUEUR NE PEUT PLUS JOUER
    while (partieTerminee(*partie, &sauvegarde,caseLigne, caseColonne) == 0)
    {
        jouer(partie, &sauvegarde);
    }
    
    // FIN DE PARTIE PROVISOIRE DUE A LA SAUVEGARDE
    if (sauvegardeFichier(*partie, &sauvegarde) == 1)
    {
        printf("Votre partie a bien été sauvegadée.\n");
    }
    
    // FIN DE PARTIE
    else
    {
        printf("La partie est terminée.\n\n");
        
        // AFFICHAGE DU VAINQUEUR
        if (partie->tabScore[0] > partie->tabScore[1])
        {
            printf("Les noirs ont gagné !\n");
        }
        else if (partie->tabScore[1] > partie->tabScore[0])
        {
            printf("Les blancs ont gagné !\n");
        }
        else
        {
            printf("C'est une égalité !\n");
        }
    }
}



void jeuOrdi(s_partie *partie)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)
    char choixPartieTemp[2] = {};
    char choixPartie = 0;
    char choixCommencementTemp[2] = {};
    char choixCommencement = 0;
    char choixModeTemp[2] = {};
    char choixMode = 0;
    int sauvegarde = 0;
    int ordinateur = 0;
    int coordonneeCaseLigne = 0;
    int coordonneeCaseColonne = 0;
    
    printf("\n");
    // INITIALISATION ET AFFICHAGE DU PLATEAU DE DEBUT DE JEU
    initialise(partie);
    printf("Pour sauvegarder en cours de partie :\n-> Entrer ligne = 0 et colonne = x \n\n");
    
    // CHOIX DE QUI COMMENCE ENTRE LE JOUEUR ET L'ORDINATEUR
   do
    {
        printf("Voulez-vous commencer <1> ou laisser l'ordinateur commencer <2> ? ");
        // %1s RECUPERE LE CARACTERE ET LE RETOUR CHARIOT
        scanf("%1s",choixCommencementTemp);
        // LE CARACTERE ETANT LE 0 ON LE RECUPERE AINSI
        choixCommencement = choixCommencementTemp[0];
        // PERMET D'EVITER UN BUG D'AFFICHAGE EN VIDANT LES CARACTERES TAPES QUI SONT EN MEMOIRE (VIDE MEMOIRE STDIN)
        while(getchar()!='\n')
        {
            continue;
        }
    } while ((choixCommencement != '1') && (choixCommencement != '2'));
    
    // SI LE JOUEUR VEUT COMMENCER
    if (choixCommencement == '1')
    {
        ordinateur = 1;
        printf("L'ordinateur jouera donc en blanc, et vous en noir.\n");
    }
    // SI C'EST L'ORDINATEUR QUI COMMENCE
    else
    {
        ordinateur = 2;
        printf("-> L'ordinateur jouera donc en noir, et vous en blanc.\n");
    }
    
    printf("\n");
    
    // CHOIX DU MODE DE JEU DE L'ORDINATEUR
    do
    {
        printf("Voulez-vous que l'ordinateur joue au hasard <1> ou de façon gloutonne <2> ? ");
        // %1s RECUPERE LE CARACTERE ET LE RETOUR CHARIOT
        scanf("%1s",choixModeTemp);
        // LE CARACTERE ETANT LE 0 ON LE RECUPERE AINSI
        choixMode = choixModeTemp[0];
        // PERMET D'EVITER UN BUG D'AFFICHAGE EN VIDANT LES CARACTERES TAPES QUI SONT EN MEMOIRE (VIDE MEMOIRE STDIN)
        while(getchar() != '\n')
        {
            continue;
        }
    } while ((choixMode != '1') && (choixMode != '2'));
    
    printf("\n");
    
    // CHOIX DE COMMENCER OU CONTINUER UNE PARTIE
    do
    {
        printf("Voulez-vous commencer une nouvelle partie <1> ou en continuer une <2> ? ");
        // %1s RECUPERE LE CARACTERE ET LE RETOUR CHARIOT
        scanf("%1s",choixPartieTemp);
        // LE CARACTERE ETANT LE 0 ON LE RECUPERE AINSI
        choixPartie = choixPartieTemp[0];
        // PERMET D'EVITER UN BUG D'AFFICHAGE EN VIDANT LES CARACTERES TAPES QUI SONT EN MEMOIRE (VIDE MEMOIRE STDIN)
        while(getchar() != '\n')
        {
            continue;
        }
        
    } while ((choixPartie != '1') && (choixPartie != '2'));
    
    // CHARGEMENT DU FICHIER DE SAUVEGARDE
    if (choixPartie == '2')
    {
        initialiseFichier(partie);
    }
    
    printf("\n\n");
    affiche(*partie);
    
    // CONDITION D'ARRET DU JEU QUAND AUCUN JOUEUR NE PEUT PLUS JOUER
    while (partieTerminee(*partie, &sauvegarde, coordonneeCaseLigne, coordonneeCaseColonne) == 0)
    {
        // SI C'EST A L'ORDINATEUR DE JOUER
        if (partie->joueurSuivant == ordinateur)
        {
            // SI LE MODE ALEATOIRE A ETE CHOISI
            if (choixMode == '1')
            {
                jouerOrdiAlea(partie);
            }
            // SI LE MODE GLOUTON A ETE CHOISI
            else
            {
                jouerOrdiGlouton(partie, &coordonneeCaseLigne, &coordonneeCaseColonne);
            }
        }
        // SI C'EST AU JOUEUR DE JOUER
        else
        {
            
            jouer(partie, &sauvegarde);
        }
    }
    
    // FIN DE PARTIE PROVISOIRE DUE A LA SAUVEGARDE
    if (sauvegarde)
    {
        printf("Votre partie a bien été sauvegadée.\n");
    }
    
    // FIN DE PARTIE
    else
    {
        printf("La partie est terminée.\n\n");
        
        // AFFICHAGE DU VAINQUEUR
        if (partie->tabScore[0] > partie->tabScore[1])
        {
            if (ordinateur == 2)
            {
                printf("Vous avez perdu !\n");
            }
            else
            {
                printf("Vous avez gagné !\n");
            }
        }
        else if (partie->tabScore[1] > partie->tabScore[0])
        {
            if (ordinateur == 2)
            {
                printf("Vous avez gagné !\n");
            }
            else
            {
                printf("Vous avez perdu !\n");
            }
        }
        else
        {
            printf("C'est une égalité !\n");
        }
    }
}



void changementJoueur(s_partie *partie)
{
    // CHANGEMENT DE JOUEUR EN FIN DE TOUR
    if (partie->joueurSuivant == 2)
    {
        partie->joueurSuivant = 1;
    }
    else
    {
        partie->joueurSuivant = 2;
    }
}