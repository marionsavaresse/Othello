
#include "possibilites.h"
#include "pose.h"
#include "plateau.h"
#include "jeu.h"
#include "modesOrdinateur.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>



void jouerOrdiAlea(s_partie *partie)
{
    srand(time(NULL));
    
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)
    int tableau[8][8] = {0};
    int nombreCoupPossible = 0;
    int ligne = 0, colonne = 0;
    char correspondanceColonne[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'x'};
    char colonneLettre;
    
    // LES COMPTEURS NE SERONT DECLARES QUE POUR LA LECTURE DU TABLEAU
    // ON PARCOURT LES CASES VIDES POUR SAVOIR SI UN COUP EST POSSIBLE QUELQUE PART
    // ON A BESOIN DE CONNAITRE LA TAILLE DU FUTUR TABLEAU, ET ON LE SAIT GRACE A CELUI CI
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if (!partie->tabPlateau[i][j])
            {
                if (coupPossible(*partie, i, j))
                {
                    nombreCoupPossible++;
                    tableau[i][j] = 1;
                }
                else
                {
                    tableau[i][j] = 0;
                }
            }
        }
    }
    
    // ON DECLARE SEULEMENT MAINTENANT POUR AVOIR LE BON NOMBRE DE LIGNES
    int tableauPossible[nombreCoupPossible][2];
    
    //INITIALISE TABLEAU
    for(int i = 0; i < nombreCoupPossible; i++)
    {
        tableauPossible[i][0] = 0;
        tableauPossible[i][1] = 0;
    }
    
    // SI AU MOINS UN COUP EST POSSIBLE
    // ON CREE NOTRE TABLEAU A DEUX COLONNES OU CHAQUE LIGNE REPRESENTE UNE CASE POSSIBLE
    // COLONNE 0 = LIGNE DE LA CASE POSSIBLE ET COLONNE 1 = COLONNE DE LA CASE POSSIBLE
    if(nombreCoupPossible > 0)
    {
        for(int i=0;i<nombreCoupPossible;i++)
        {

            for(int k=0;k<8;k++)
            {
                for(int l=0;l<8;l++)
                {
                    if(tableau[k][l] == 1)
                    {
                        tableauPossible[i][0] = k;
                        tableauPossible[i][1] = l;
                    }
                }
            }
        }
        
        // CHOIX AU HASARD DE LA CASE SUR LAQUELLE IL VA JOUER
        int hasard = rand()%(nombreCoupPossible);
        ligne = tableauPossible[hasard][0];
        colonne = tableauPossible[hasard][1];
   
        // TRANSFORMATION DE LA COLONNE
        for (int i = 0; i < 8; i++)
        {
            if (colonne == i)
            {
                colonneLettre = correspondanceColonne[i];
            }
        }
        
        jouerCase(partie, ligne, colonne);
        affiche(*partie);
        printf("L'ordinateur a joué en %d%c.\n\n",ligne+1,colonneLettre);
        changementJoueur(partie);
    }
    // SI AUCUN COUP N'EST POSSIBLE
    else
    {
        printf("L'ordinateur ne peut pas jouer, il passe donc son tour.\n\n");
        changementJoueur(partie);
    }

}



void jouerOrdiGlouton(s_partie *partie, int *ligne, int *colonne)
{
    // DECLARATION DE VARIABLES (ON LES INITIALISE TOUJOURS)
    char correspondanceColonne[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'x'};
    char colonneLettre;
    
    // SI L'ORDINATEUR PEUT JOUER
    if (possible(*partie, ligne, colonne))
    {
        // TRANSFORMATION DE LA COLONNE
        for (int i = 0; i < 8; i++)
        {
            if (*colonne == i)
            {
                colonneLettre = correspondanceColonne[i];
            }
        }
        
        jouerCase(partie, *ligne, *colonne);
        affiche(*partie);
        printf("L'ordinateur a joué en %d%c.\n\n",*ligne+1,colonneLettre);
        changementJoueur(partie);
    }
    // SI L'ORDINATEUR NE PEUT PAS JOUER
    else
    {
        printf("L'ordinateur ne peut pas jouer, il passe donc son tour.\n\n");
        changementJoueur(partie);
    }
}