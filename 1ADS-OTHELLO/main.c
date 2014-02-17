#include <stdio.h>

#include "possibilites.h"
#include "jeu.h"

int main()
{
    // DECLARATION DE LA STRUCTURE DE LA PARTIE
    s_partie partie;
    
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)  
    char choixTemp[2] = {};
    char choix = 0;
    
    // MESSAGE DE BIENVENUE
    printf("Bienvenue dans le monde fantastique de l'Othello !\n\n");
    
    // CHOIX DU JOUEUR SUR LE MODE DE JEU
    do
    {
        printf("Voulez-vous jouer à deux joueurs <1> ou contre l'ordinateur <2> ? ");
        // %1s RECUPERE LE CARACTERE ET LE RETOUR CHARIOT
        scanf("%1s",choixTemp);
        // LE CARACTERE ETANT LE 0 ON LE RECUPERE AINSI
        choix = choixTemp[0];
        // PERMET D'EVITER UN BUG D'AFFICHAGE EN VIDANT LES CARACTERES TAPES QUI SONT EN MEMOIRE (VIDE MEMOIRE STDIN)
        while(getchar()!='\n')
        {
            continue;
        }
    } while ((choix != '1') && (choix != '2'));
    
    // SI LE JOUEUR CHOISI DE JOUER CONTRE UN AUTRE JOUEUR
    if (choix == '1')
    {
        printf("-> Vous jouez en mode JcJ.\n");
        jeuDeux(&partie);
    }
    // SI LE JOUEUR VEUT JOUER CONTRE L'ORDINATEUR
    else
    {
        printf("-> Vous jouez contre l'ordinateur.\n");
        jeuOrdi(&partie);
    }
    
    return 0;
}

