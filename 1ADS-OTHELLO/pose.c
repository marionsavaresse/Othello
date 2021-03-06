#include <stdio.h>

#include "possibilites.h"
#include "plateau.h"
#include "pose.h"
#include "sauvegarde.h"
#include "jeu.h"


void majScore(s_partie *partie);
void testCoupDirection(s_partie *partie, int ligne, int colonne, int abscisse, int ordonnee);



void jouerCaseDirection(s_partie *partie, int ligne, int colonne, int abscisse, int ordonnee)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)
    int pionAdverse = 0, pionJoueur = 0;

    // IDENTIFICATION DU JOUEUR
    identificationJoueur(*partie, &pionJoueur, &pionAdverse);
  
    // CHANGEMENT DE COULEUR DES PIONS DANS UNE DIRECTION DONNEE
    do
    {
        partie->tabPlateau[ligne][colonne] = pionJoueur;
            
        ligne += abscisse;
        colonne += ordonnee;
            
        partie->tabPlateau[ligne][colonne] = pionJoueur;

    }
    while (partie->tabPlateau[ligne+abscisse][colonne+ordonnee] == pionAdverse);
    

    // ON MET LE SCORE A JOUR APRES CHAQUE TOUR
    majScore(partie);
}



void jouerCase(s_partie *partie, int ligne, int colonne)
{
    // SI UNE DIRECTION EST POSSIBLE, ON PEUT JOUER ET RETOURNER LES PIONS DE CETTE DIRECTION
    if (coupPossibleDirection(*partie, ligne, colonne, -1, 0))
    {
        jouerCaseDirection(partie, ligne, colonne, -1, 0);
    }
    if (coupPossibleDirection(*partie, ligne, colonne, -1, 1))
    {
        jouerCaseDirection(partie, ligne, colonne, -1, 1);
    }
    if (coupPossibleDirection(*partie, ligne, colonne, 0, 1))
    {
        jouerCaseDirection(partie, ligne, colonne, 0, 1);
    }
    if (coupPossibleDirection(*partie, ligne, colonne, 1, 1))
    {
        jouerCaseDirection(partie, ligne, colonne, 1, 1);
    }
    if (coupPossibleDirection(*partie, ligne, colonne, 1, 0))
    {
        jouerCaseDirection(partie, ligne, colonne, 1, 0);
    }
    if (coupPossibleDirection(*partie, ligne, colonne, 1, -1))
    {
        jouerCaseDirection(partie, ligne, colonne, 1, -1);
    }
    if (coupPossibleDirection(*partie, ligne, colonne, 0, -1))
    {
        jouerCaseDirection(partie, ligne, colonne, 0, -1);
    }
    if (coupPossibleDirection(*partie, ligne, colonne, -1, -1))
    {
        jouerCaseDirection(partie, ligne, colonne, -1, -1);
    }
}



void jouer(s_partie *partie, int *sauvegarde)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)    
    // LES TABLEAUX TEMPORAIRES STOCKERONT LE RETOUR CHARIOT PRIS EN COMPTE DANS LES FUTUR SCANF
    int ligne = 0;
    int colonne = 0;
    int caseLigne = 0;
    int caseColonne = 0;
    char colonneLettreTemp[2] = {};
    char colonneLettre = 0;
    char ligneLettreTemp[2]= {};
    char ligneLettre = 0;
    char correspondanceLigne[] = {'0','1', '2', '3', '4', '5', '6', '7', '8'};
    char correspondanceColonne[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'x'};
    
    // IDENTIFICATION DU JOUEUR QUI DOIT JOUER
    if (partie->joueurSuivant == 2)
    {
        printf("C'est aux noirs de jouer.\n\n");
    }
    else
    {
        printf("C'est aux blancs de jouer.\n\n");
    }
    
    // SI AU MOINS UN COUP EST POSSIBLE PAR LE JOUEUR
    if (possible(*partie, &caseLigne, &caseColonne) == 1)
    {
        do
        {
            // RENTREE DE LA LIGNE PAR LE JOUEUR
            do
            {
                printf("Saisir le numéro de la ligne où vous voulez jouer : ");
                // %1s RECUPERE LE CARACTERE ET LE RETOUR CHARIOT
                scanf("%1s",ligneLettreTemp);
                // LE CARACTERE ETANT LE 0 ON LE RECUPERE AINSI
                ligneLettre = ligneLettreTemp[0];
                // PERMET D'EVITER UN BUG D'AFFICHAGE EN VIDANT LES CARACTERES TAPES QUI SONT EN MEMOIRE (VIDE MEMOIRE STDIN)
                while(getchar() != '\n')
                {
                    continue;
                }
            } while ((ligneLettre < '0') || (ligneLettre > '8'));
        
            // TRANSFORMATION DE LA LIGNE
            for(int i = 0; i < 9; i++)
            {
                if(correspondanceLigne[i] == ligneLettre)
                {
                    ligne = i-1;
                }
            }
        
            // RENTREE DE LA COLONNE PAR LE JOUEUR
            do
            {
                printf("Saisir la lettre de la colonne où vous voulez jouer : ");
                // %1s RECUPERE LE CARACTERE ET LE RETOUR CHARIOT (PAS BESOIN DE & CAR C'EST UN TABLEAU)
                scanf("%1s",colonneLettreTemp);
                // LE CARACTERE ETANT LE 0 ON LE RECUPERE AINSI
                colonneLettre = colonneLettreTemp[0];
                // PERMET D'EVITER UN BUG D'AFFICHAGE EN VIDANT LES CARACTERES TAPES QUI SONT EN MEMOIRE (VIDE MEMOIRE STDIN)
                while(getchar() != '\n')
                {
                    continue;
                }
            } while (((colonneLettre < 'a' || colonneLettre > 'h') && (colonneLettre < 'A' || colonneLettre > 'H')) && (colonneLettre != 'x' && colonneLettre != 'X'));
            
            // TRANSFORMATION DE LA COLONNE
            if ((colonneLettre >= 'A' && colonneLettre <= 'H') || colonneLettre == 'X')
            {
                colonneLettre += 32;
            }
            
            for(int i = 0; i < 8; i++)
            {
                if(correspondanceColonne[i] == colonneLettre)
                {
                    colonne = i;
                }
            }
        } while (((ligneLettre < '1' && ligneLettre > '8') && (colonneLettre < 'a' && colonneLettre > 'h')) ^ (ligneLettre == '0' && colonneLettre != 'x'));
        
                printf("\n\n");
        
        if (ligneLettre != '0' && colonneLettre != 'x')
        {
        
            // SI LE JOUEUR RENTRE DES COORDONNES OU L'ON PEUT JOUER
            if (coupPossible(*partie, ligne, colonne))
            {
                jouerCase(partie, ligne, colonne);
                affiche(*partie);
                changementJoueur(partie);
            }
            // SI LE JOUEUR RENTRE DES COORDONNEES OU IL NE PEUT PAS JOUER
            else
            {
                printf("Vous pouvez jouer, mais pas sur cette case.\n");
                printf("Veuillez saisir une case valide.\n\n");
                jouer(partie, sauvegarde);
            }
        }
        // SI LE JOUEUR A SOUHAITE SAUVEGARDER
        else
        {
            *sauvegarde = 1;
            sauvegardeFichier(*partie, sauvegarde);
            partieTerminee(*partie, sauvegarde, caseLigne, caseColonne);
        }
    }
    
    // SI AUCUN COUP N'EST POSSIBLE PAR LE JOUEUR
    else
    {
        printf("Vous ne pouvez pas jouer, vous passez donc votre tour.\n\n");
        changementJoueur(partie);
    }
}



// MISE A JOUR DU SCORE
void majScore(s_partie *partie)
{
    int noirs = 0;
    int blancs = 0;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(partie->tabPlateau[i][j] == 1)
            {
                blancs++;
            } else if (partie->tabPlateau[i][j] == 2)
            {
                noirs++;
            }
        }
    }
    partie->tabScore[0] = noirs;
    partie->tabScore[1] = blancs;
    
    printf("\n");
}